#include "sf_db/sf_db.h"

#include <algorithm>
#include <sstream>
#include <boost/algorithm/string.hpp>

void checkError(SQLRETURN retcode, std::string msg) {
    if ((retcode != SQL_SUCCESS) && (retcode = !SQL_SUCCESS_WITH_INFO)) {
        std::cerr << msg << std::endl;
    }
    assert(retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO);
}

bool checkErrorCode(SQLRETURN retcode) {
    if ((retcode != SQL_SUCCESS) && (retcode = !SQL_SUCCESS_WITH_INFO)) {
        return false;
    }
    return true;
}

SFConnection::SFConnection(DBAuthorization auth) : m_auth(auth) {
    // Allocate environment handle
    henv_ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    checkError(henv_ret, "SQLAllocHandle failed");
    // Set the ODBC version environment attribute

    henv_ret =
        SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);

    checkError(henv_ret, "SQLSetEnvAttr failed");
    // Allocate connection handle

    hdbc_ret = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    checkError(hdbc_ret, "SQLAllocHandle failed");
    // Set login timeout to 5 seconds

    SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

    // Connect to data source
    hdbc_conn_ret = SQLConnect(hdbc, (SQLCHAR *)m_auth.dataSource.data(),
                               SQL_NTS, (SQLCHAR *)NULL, 0,
                               (SQLCHAR *)m_auth.password.data(), SQL_NTS);

    checkError(hdbc_conn_ret, "SQLConnect connect to product_odbc failed");

    std::cout << "connect to product_odbc success!" << std::endl;
}

std::vector<std::string> SFConnection::parse_fields_from_query_string(
    std::string query_string) {

    std::vector<std::string> result {};
    std::transform(query_string.begin(), query_string.end(),
                   query_string.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    auto start = query_string.find("select") + 6;
    auto end = query_string.find("from") - 1;
    auto fields_string = query_string.substr(start, end - start);
    std::stringstream ss(fields_string);
    std::string field{};
    while(std::getline(ss, field, ',')) {
        boost::trim(field);
        result.emplace_back(std::move(field));
    }
    return std::move(result);
}

SFConnection::DB_RETURN_TYPE SFConnection::exec_query(
    std::string query_string) {
    DB_RETURN_TYPE results;

    std::vector<std::string> field_names = parse_fields_from_query_string(query_string);

    SQLHSTMT hstmt;

    std::vector<std::array<SQLCHAR, 2000>> field_values {};
    std::array<SQLCHAR, 2000> field_value {};
    field_values.resize(field_names.size(), field_value);

    std::vector<SQLLEN> field_lens {};
    field_lens.resize(field_names.size(), 0);

    // Allocate statement handle

    auto hstmt_ret = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);

    if (!checkErrorCode(hstmt_ret)) {
        std::cerr << "SQLAllocHandle statement failed!" << std::endl;
        return results;
    }

    auto retcode =
        SQLExecDirect(hstmt, (SQLCHAR *)query_string.data(), SQL_NTS);

    if (!checkErrorCode(retcode)) {
        std::cerr << "SQLExecDirect failed!" << std::endl;
        goto ERROR_;
    }

    for(int i=0; i<field_names.size(); ++i) {
        SQLCHAR* tmpFieldValue = field_values[i].data();
        retcode = SQLBindCol(hstmt, i+1, SQL_C_CHAR, tmpFieldValue, 2000, &field_lens[i]);
    }

    // Fetch and print each row of data until
    // SQL_NO_DATA returned.
    for (int i = 0;; i++) {
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
            std::cout << i+1 << " ";
            std::map<std::string, std::string> tmp_fields{};

            for(int j=0; j<field_names.size(); ++j) {
                std::string temp_field((const char*)field_values[j].data(), field_lens[j]);
                std::cout << temp_field << " ";
                tmp_fields[field_names[j]] = temp_field;
            }
            std::cout << std::endl;

            results.emplace_back(std::move(tmp_fields));

        } else {
            if (retcode != SQL_NO_DATA) {
                std::cout << "SQLFetch Error, error code: " << retcode
                          << std::endl;
                break;
            } else {
                break;
            }
        }
    }
ERROR_:
    std::cout << "Free statement" << std::endl;
    SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
    return std::move(results);
}

SFConnection::~SFConnection() {
    if (checkErrorCode(hdbc_conn_ret)) {
        SQLDisconnect(hdbc);
        std::cout << "Free connection" << std::endl;
    }

    if (checkErrorCode(hdbc_ret)) {
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        std::cout << "Free dbc" << std::endl;
    }

    if (checkErrorCode(henv_ret)) {
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
        std::cout << "Free env" << std::endl;
    }
}