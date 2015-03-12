#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unistd.h>

int main(int argc,char **argv)
{
  int c;//for getopt
  char input='n';//input delimiter
  std::string output="n";//output delimiter

  //Options for delimiters
  while((c=getopt(argc,argv,"xyzabc"))!=-1)
    {
      switch(c)
	{
	case 'x':
	  input=',';
	  break;
	case 'y':
	  input=' ';
	  break;
	case 'z':
	  input='\t';
	  break;

	case 'a':
	  output=",";
	  break;
	case 'b':
	  output=" ";
	  break;
	case 'c':
	  output="\t";
	  break;

	default:
	  std::cout<<"Set Options: \n\t input:  x(,) y( ) z(tab)\n\t output: a(,) b( ) c(tab)\n"<<std::endl;
	  std::cout<<".exe -y -a input.txt output.txt"<<std::endl;
	  return -1;
	}
    }
  //When options lack
  if(input=='n'||output=="n")
    {
      std::cout<<"Set Options: \n\t input:  x(,) y( ) z(tab)\n\t output: a(,) b( ) c(tab)\n"<<std::endl;
      std::cout<<".exe -y -a input.txt output.txt"<<std::endl;
      return -1;
    }
  
  std::ifstream fin(argv[3]);
  std::string temp;//for getline
  std::vector<std::string> v;
  while (getline(fin,temp,input))
    {
      if(temp.size()!=0)
	{
	  v.push_back(temp);
	  v.push_back(output);
	}
    }
  v.pop_back();//delete a superfluous output delimiter

  //Writing out
  std::ofstream fout(argv[4]);
  for(auto s:v)
    {
      fout<<s;
    }
}
