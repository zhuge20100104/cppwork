FROM registry.appannie.org/appannie/aa-docker-test/fedora-cpp:v1.2.1
ENV CMAKE_INCLUDE_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/include
ENV CMAKE_LIBRARY_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/lib
ENV ODBCINI /etc/odbc.ini
ENV ODBCSYSINI /etc
ENV GTEST_CATCH_EXCEPTIONS 0
ENV PATH /vcpkg:$PATH

