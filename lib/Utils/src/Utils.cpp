#include <Utils.h>
/**
 * @brief Prints "Hello Chat" a few Times
 * 
 * @param t_howmany How often print "Hello Chat"
 * @param t_stream Where to print
 * @note Example-Call
 * @code .cpp
 * helloWorldFkt(Serial, 12);
 * @endcode 
 */
void helloWorldFkt(Stream& t_stream, int t_howmany){
  for (int i=0; i<t_howmany;i++){
    t_stream.println("Hello Chat");
  }
}