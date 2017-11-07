#include <iostream>
#include <cstring>

class string {
public:
  string(int n = 0);
  string(const char *b); 
  string(const string &rhs); 
  ~string() { delete [] buf; }

  const char* getBuf() const { return buf; }
  void setBuf(const char* b);
  size_t size() const { return strlen(buf); }
  string& operator=(const string& rhs);

  const char& operator[](int index) const { 
    std::cout << "const []" << std::endl;
    return buf[index]; 
  }

  char& operator[](int index) { 
    std::cout << "non const []" << std::endl;
    return buf[index]; 
  }

  const string operator+(const char*) const;
  const string operator+(const string&) const;
  bool operator==(const string& rhs) const { return strcmp(buf,rhs.buf)==0; }
private:
  char *buf;
};
std::ostream& operator<<(std::ostream&, const string&);
const string operator+(const char*, const string&);

