#include <iostream>
#include <windows.h>
#include <MySQL/mysql.h>
#include <string>
#include <time.h>

std::string DateTimeNow();

int main(int argc, char const** argv)
{
    if(argc < 5) return -1;
    char const* host        = argv[1];
    char const* user        = argv[2];
    char const* password    = argv[3];
    char const* db          = argv[4];
    char const* table       = argv[5];
    char const* values      = argv[6];
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn, host, user, password, db, 0, NULL, 0);
    if(conn)    std::cout << "Connected successfully\n";
    else        std::cerr << "The connection has been failed\n";
    std::string ss;
    ss = std::string("INSERT INTO ") + table + " values(" + values + ", '" + DateTimeNow() + "');";
    int qstate = mysql_query(conn, ss.c_str());
    std::cout << "[Action]: " << ss << '\n';
    if(!qstate)     std::cout << "[Result]: Okay\n";
    else            std::cerr << "[Result]: Fatal error\n";
}

std::string DateTimeNow()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}
