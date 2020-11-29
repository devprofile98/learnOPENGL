#include <iostream>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


uint32_t total_allocation = 0;
// void* operator new(size_t size){
    
//     // return ::new(size); is not valid outside of class type as member function
//     std::cout<<"allocate "<<size <<" byte on heap"<<std::endl;
//     total_allocation +=size;
//     return malloc(size);
// }

void operator delete(void* address){
    std::cout<<"free "<<address<<" from heap "<< sizeof(address)<<std::endl;
    total_allocation-=sizeof(address);
}



int main(){

    glm::vec4 vec(1.0f,0.0f,0.0f,1.0f);
    glm::mat4 trans{1.0f};
    trans = glm::translate(trans,glm::vec3(1.0f,1.0f,0.0f));
    vec = vec*trans;
    std::cout<<vec.x<<" "<<vec.y<<" "<<vec.z<<std::endl;

    int sizee[9];
    int *size = new int(10);
    std::cout<<"allocating array "<<std::endl;

    for(int i =0;i<20;i++)
        sizee[i] = i;

    for(int i =0;i<30;i++){
        std::cout<<sizee[i]<<" ";
    }

    std::cout<<"ending array allocating "<<sizee[13]<<std::endl;
    delete[] size;

    std::cout<<"final total allocation that created and deleted from memory is "<<total_allocation<<std::endl;


    return 0;
}