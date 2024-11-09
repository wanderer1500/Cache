#include <bits/stdc++.h>
#define int long long
using namespace std;
double hits = 0;
double requests = 0;
class Cache
{
public:
    vector<vector<int>> State;
    vector<vector<int>> Tag;
    vector<vector<vector<int>>> Data;

    // Constructor to initialize 'State', 'Tag', and 'Data'
    Cache() : State(64, vector<int>(8, 0)),
              Tag(64, vector<int>(8, -1)),
              Data(64, vector<vector<int>>(8, vector<int>(16, -1)))
    {
    }
};
const int Adress_Size = 40;
const int Block_Size = 16;

vector<int> DataBlockGen(){
    vector<int> datas(16,0);
    for(int i=0;i<16;i++){
        datas[i]=rand();
    }
    return datas;
}

int BlockNumGen(){
    return rand()%8;
}

void Replace_Block(Cache &L, int Adress, int block_number, vector<int> datas)
{
    int blockOffset = ((Adress) / 4) % Block_Size;
    int remaining = (Adress >> (6));
    int index = (remaining % 64);
    int tag = (Adress >> 12);

    L.State[index][block_number] = 1;
    L.Tag[index][block_number] = tag;
    cout<<"Block Is Getting Replaced\n";
    for (int i = 0; i < 16; i++)
    {    
        L.Data[index][block_number][i] = datas[i];
    }
    cout<<"Block Replacement Is Completed\n";

}

bool isHit(Cache &L, int Adress)
{
    int blockOffset = ((Adress) / 4) % Block_Size;
    int remaining = (Adress >> (6));
    int index = (remaining % 64);
    int tag = (Adress >> 12);
    for (int i = 0; i < 8; i++)
    {
        if (L.State[index][i] && L.Tag[index][i] == tag)
        {

            cout << "Data Present is:" << L.Data[index][i][blockOffset] << "\n";
            return true;
        }
    }

    return false;
}

void Read_Req(Cache &L, int Adress)
{
    int blockOffset = ((Adress) / 4) % Block_Size;
    int remaining = (Adress >> (6));
    int index = (remaining % 64);
    int tag = (Adress >> 12);
    if (isHit(L, Adress))
    {
        cout << "It's a Hit\n";
        hits++;
        return;
    }
    else
    {

        cout << "Adress is not Present It is a miss\n";
        vector<int> datas=DataBlockGen();
        int block_num=BlockNumGen();
        Replace_Block(L,Adress,block_num,datas);
       
        // Random Generate Block and Replace
    }
}
void Write_Req(Cache &L, int Adress)
{
    int blockOffset = ((Adress) / 4) % Block_Size;
    int remaining = (Adress >> (6));
    int index = (remaining % 64);
    int tag = (Adress >> 12);
    if (isHit(L, Adress))
    {   
        cout << "It's a Hit\n";
        hits++;
        cout << "Memory Request is Sent To Write Through\n";
        return;
    }
    else
    {
        cout << "It's a miss\n";
        vector<int> datas=DataBlockGen();
        int block_num=BlockNumGen();
        Replace_Block(L,Adress,block_num,datas);
        cout << "Memory Request is Sent\n";
    }
}
uint64_t generate_40_bit_random_normal() {
    random_device rd;
    mt19937_64 gen(rd());

    // Normal distribution with a mean around (1ULL << 37) for mid-range and stddev to cover the desired range
    normal_distribution<double> dist(static_cast<double>(1ULL << 37), static_cast<double>(1000ULL));

    uint64_t address;
    do {
        address = static_cast<uint64_t>(dist(gen));
    } while (address >= (1ULL << 38)); // Ensure it stays within the 38-bit range

    // return (address*4)%(1<<12);
    return (address*4);

}
int32_t main()
{
    Cache L;
    int vec = L.State[1][0];
    cout << vec << "\n";

    requests = 0;
    hits = 0;
    long long  n=1e10;
    while (n--)
    {
        int random_req = rand() % 2;
        requests++;
         uint64_t mean = (1ULL << 39);            // 2^39
    uint64_t stddev = (1ULL << 38);          // Standard deviation, adjust as needed

    // Seed with a random device for randomness
    std::random_device rd;
    std::mt19937_64 gen(rd()); // 64-bit generator for large ranges
    std::normal_distribution<double> dist(mean, stddev);

    // Generate a random number
    uint64_t random_number = static_cast<uint64_t>(dist(gen));

    // Clamp the random number within [0, 2^40 - 1] range
    uint64_t max_value = (1ULL << 40) - 1;
    if (random_number > max_value) random_number = max_value;
    if (random_number < 0) random_number = 0;

    // Generate a random number
    
        int random_Adress = generate_40_bit_random_normal();
        if (random_req)
        { // Write_Req
            cout<<"It's a Write Request\n";
            Write_Req(L, random_Adress);
        }
        else
        { // Read_Req
            cout<<"It's a Read Request\n";
            Read_Req(L, random_Adress);
        }

        double hit_rate = (hits / requests) * 100;
        cout << "After " << requests << " Requests and ," <<hits<<" Hits "<<"Hit Rate is " << hit_rate << "\n";
    }
    // Further operations with 'cache'
}
