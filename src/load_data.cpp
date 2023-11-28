#include <iostream>
#include <arm_neon.h>
#include<stdio.h>

float array[]={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
float array2[]={3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0};

void test()
{
    float32x4_t _p1 = vld1q_f32(array);
    float32x4_t _p2 = vld1q_f32(array2);
    vst1q_f32(array2,_p1);
    vst1q_f32(array,_p2);
}

int main()
{
    test();
    for(int i=0;i<8;i++)
    {
        std::cout<<array[i]<<std::endl;
    }


    for(int i=0;i<8;i++)
    {
        std::cout<<array2[i]<<std::endl;
    }
    return 0;
}