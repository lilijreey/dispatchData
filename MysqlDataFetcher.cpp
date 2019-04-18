#include <mysql.h>
#include <stdio.h>
#include <string>
#include <assert.h>


//TOOD notcopy
class MySqlClient 
{
 public:
  MySqlClient() 
  {
      _mysql = mysql_init(NULL);
  }
  ~MySqlClient()
  {
      if (_mysql)
      {
          mysql_close(_mysql);
          _mysql = nullptr;
      }
  }

  class MySqlResult
  {



  };

 public:
    
    inline static const char *GetInfo() 
    {
        return mysql_get_client_info();
    }

    bool Connect(const std::string &host, 
                 const std::string &user, 
                 const std::string &passwd, 
                 const std::string &db,
                 unsigned port)
    {
        assert(_mysql);
        return mysql_real_connect(_mysql, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0);
    }

    const char* GetError() const 
    {
        if (_mysql)
            return mysql_error(_mysql);
        return "INIT MYSQL FAILED";
    }

    bool RealQuery(const std::string &sql)
    {
        return mysql_real_query(_mysql, sql.c_str(), sql.length()) == 0;
    }

    MySqlResult StoreResult()
    {

    }

    unsigned FieldCount() 
    {
        return mysql_field_count(_mysql);
    }

    MYSQL *_mysql{};
};

int main(int argc, char *argv[])
{
      printf("MySQL client version: %s\n", MySqlClient::GetInfo());
      MySqlClient mysql;
      std::string dbHost = "127.0.0.1";
      std::string dbUser = "root";
      std::string dbPass = "12345";
      std::string dbName = "test";
      unsigned dbPort = 3306;

      //TODO timeout
      if (not mysql.Connect(dbHost, dbUser, dbPass, dbName, dbPort))
      {
          printf("conn failed :%s\n", mysql.GetError());
          exit(0);
      }

      if (not mysql.RealQuery("select * from vote_record;"))
      {
          printf("query failed :%s\n", mysql.GetError());
          exit(0);
      }


      printf("row count:%u\n", mysql.FieldCount());

      printf("conn ok\n");


    
    return 0;
}
