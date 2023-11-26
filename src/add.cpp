#include <iostream>
#include <cstdlib>
#include <ctime>
#include <arm_neon.h>
#include <benchmark/benchmark.h>

const int ARRAY_SIZE = 100000000;

int a[ARRAY_SIZE];
int b[ARRAY_SIZE];
int c[ARRAY_SIZE];

void add(const int* a,const int* b,int* c,int len) 
{
  for(int i=0;i<len;i++)
  {
    c[i] = a[i]+b[i];
  }
}

void add_vector(const int* a,const int* b,int* c,int len) 
{
    int i;
    int32x4_t va, vb, vc;
    
    for (i = 0; i < len; i += 4)
    {
        // ���ڴ���� 4 �������� NEON �Ĵ���
        va = vld1q_s32(a + i);
        vb = vld1q_s32(b + i);
        
        // ִ�мӷ�����
        vc = vaddq_s32(va, vb);
        
        // ������洢���ڴ���
        vst1q_s32(c + i, vc);
    }
}

void add_vector_mp(const int* a,const int* b,int* c,int len) 
{
    int i;
    int32x4_t va, vb, vc;
    #pragma omp parallel for num_threads(8)
    for (i = 0; i < len; i += 4)
    {
        // ���ڴ���� 4 �������� NEON �Ĵ���
        va = vld1q_s32(a + i);
        vb = vld1q_s32(b + i);
        
        // ִ�мӷ�����
        vc = vaddq_s32(va, vb);
        
        // ������洢���ڴ���
        vst1q_s32(c + i, vc);
    }
}

static void test_add(benchmark::State& state)
{    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < ARRAY_SIZE; ++i) 
    {
        a[i] = std::rand();
        b[i] = std::rand();
    }
    
    for (auto _ : state) 
    {
        add(a,b,c,ARRAY_SIZE);
    }
    
}

static void test_add_vector(benchmark::State& state)
{    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < ARRAY_SIZE; ++i) 
    {
        a[i] = std::rand();
        b[i] = std::rand();
    }
    
    for (auto _ : state) 
    {
        add_vector(a,b,c,ARRAY_SIZE);
    }
    
}

static void test_add_vector_mp(benchmark::State& state)
{    
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    for (int i = 0; i < ARRAY_SIZE; ++i) 
    {
        a[i] = std::rand();
        b[i] = std::rand();
    }
    
    for (auto _ : state) 
    {
        add_vector_mp(a,b,c,ARRAY_SIZE);
    }
    
}

BENCHMARK(test_add);
BENCHMARK(test_add_vector);
BENCHMARK(test_add_vector_mp);



BENCHMARK_MAIN();