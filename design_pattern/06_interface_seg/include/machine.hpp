#ifndef _FREDRIC_MACHINE_HPP_
#define _FREDRIC_MACHINE_HPP_

#include <string>
#include <concepts>
#include <iostream>
#include <utility>

struct Document {
    std::string text;
};

template <typename T>
concept PrintType = requires (const T value) {
    value.print(std::declval<Document&>());
};

template <typename T>
concept ScannerType = requires (const T value) {
    value.scan(std::declval<Document&>());
};

template <typename T>
concept FaxType = requires (const T value) {
    value.fax(std::declval<Document&>());
};

template <PrintType PrintT>
struct Printer {
    PrintT const& printer;
    Printer(PrintT const& printer_): printer{printer_} {}

    void print(Document& doc) const{
        printer.print(doc);
    }
};

template <PrintType PrintT, ScannerType ScanT>
struct Machine {
    PrintT const& printer;
    ScanT const& scanner;

    Machine(PrintT const& printer_, ScanT const& scanner_): printer{printer_}, scanner{scanner_} {}

    void print(Document& doc) const {
        printer.print(doc);
    }

    void scan(Document& doc) const {
        scanner.scan(doc);
    }
};

struct PrintImpl {
    void print(Document& doc) const{
        std::cout << "PrintImpl print: " << doc.text << "\n";
    }
};

struct ScannerImpl {
    void scan(Document& doc) const{
        std::cout << "ScannerImpl scan: " << doc.text << "\n";
    }
};
#endif