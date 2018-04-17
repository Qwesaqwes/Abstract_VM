#include <stdio.h>

int main ()
{
  if( remove( "test_files/myfile.txt" ) != 0 )
    perror( "Error deleting file" );
  else
    puts( "File successfully deleted" );
  return 0;
}
