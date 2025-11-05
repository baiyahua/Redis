#include <iostream>
#include <sw/redis++/redis++.h>

int main()
{
    sw::redis::Redis client("tcp://127.0.0.1:6379");
    std::string result = client.ping();
    std::cout << result << std::endl;
    return 0;
}