#pragma comment(lib, "Ws2_32.lib")
// charEndian.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>

#include <WinSock2.h>

#pragma pack(push, 1)
struct Pack1 {
    uint16_t id;
    uint16_t val;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Pack2 {
    uint32_t first;
    uint32_t second;
    uint32_t third;
};

void changeVector(void* data) {

    char* ptr2 = static_cast<char*>(data);

    Pack1* pack1Parse = reinterpret_cast<Pack1*>(ptr2);
    pack1Parse->id = 3;
    pack1Parse->val = 30;

    Pack2* pack2Parse = reinterpret_cast<Pack2*>(ptr2 + sizeof(Pack1));
    //pack2Parse->first *= 2;
    //pack2Parse->second *= 3;
    //pack2Parse->third *= 4;
    pack2Parse->first = htonl(pack2Parse->first);
    pack2Parse->second = htonl(pack2Parse->second);
    pack2Parse->third = htonl(pack2Parse->third);
}

int main()
{
    std::vector<unsigned char> v1(sizeof(Pack1)+sizeof(Pack2), 0x00);
    
    Pack1* pack1Ptr = reinterpret_cast<Pack1*>(v1.data());
    pack1Ptr->id = 1;
    pack1Ptr->val = 10;

    unsigned char* ptr1 = reinterpret_cast<unsigned char*>(pack1Ptr + 1);

    Pack2* pack2Ptr = reinterpret_cast<Pack2*>(ptr1);
    pack2Ptr->first = 25;
    pack2Ptr->second = 125;
    pack2Ptr->third = 325;

    printf("\n");
    for (auto i : v1)
        printf("%d ", i);
    printf("\n");

    changeVector(v1.data());

    printf("\n");
    for (auto i : v1)
        printf("%d ", i);
    printf("\n");

    getchar();
    return 0;
}

