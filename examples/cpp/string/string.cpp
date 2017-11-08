#include "string.h"

std::ostream& operator<<(std::ostream& out, const string& s) {
  return out << s.getBuf();
}

const string operator+(const char* lhs, const string& rhs) {
  string sum(lhs);
  sum = sum+rhs;
  return sum;
}

string::string(int n) : buf(new char[n+11]) { buf[0] = '\0'; }

string::string(const char *b) 
  : buf(new char[strlen(b)+1]) {
  strcpy(buf, b);
}

string::string(const string &rhs) 
  : buf(new char[strlen(rhs.buf)+1]) {
  strcpy(buf, rhs.buf);
}

const string string::operator+(const string& rhs) const {
  string sum(strlen(buf)+rhs.size()+1);
  strcpy(sum.buf, buf);
  strcat(sum.buf,rhs.buf);
  return sum;
}

void string::setBuf(const char* b) { 
  if ( b == nullptr ) return;
  delete [] buf;
  buf = new char[strlen(b)+1];
  strcpy(buf, b);
}

string& string::operator=(const string& rhs) {
  if ( &rhs == this ) return *this;
  delete [] buf;
  buf = new char[strlen(rhs.buf)+1];
  strcpy(buf, rhs.buf);
  return *this;
}

