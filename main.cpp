//        Class template - done
//        No STL containers - done
//        Smart pointers - done
//        Copy and move constructors - done
//        Assignment and move operators - done
//        Method for adding an element - done
//        Method for searching an element - done
//        Method for sorting (in case of sequential data structures) - done
//        Method for (de)serialization - done

#include "linked_list.h"
int main(){
    List<int> lista();
    List<int>lista2(17);
      lista2.display();
    lista2.add_element(lista2.head,21);
     std::cout<<"====================lista 2 after adding an element========================="<<std::endl;
    lista2.add_element(lista2.head,217);
     lista2.display();
    List<int> lista1(lista2);
     std::cout<<"=====================list created with copy constructor========================"<<std::endl;
    lista1.display();
      std::cout<<"=====================list created with move constructor========================"<<std::endl;
    List<int> lista3 = std::move(lista1);
     lista3.display();
    std::cout<<"====================list moved========================="<<std::endl;
    lista1.display();
      std::cout<<"======================new created list======================="<<std::endl;
    List<int>lista4(1420);
    lista4.add_element(lista4.head,6);
      lista4.display();
    List<int>lista5(13);
    lista5 = lista4;
      std::cout<<"======================list after using copy assignment operator======================="<<std::endl;
    lista4 = lista3;
     lista4.display();
std::cout<<"====================list after using move assignment operator========================="<<std::endl;
    lista5 = std::move(lista4);
     lista5.display();
     std::cout<<"=====================moved list========================"<<std::endl;
    lista4.display();
     std::cout<<"=======================searching for value 217 in list======================"<<std::endl;
     std::cout<<lista5.search(217)<<std::endl;
    std::cout<<"======================sort======================="<<std::endl;
    lista5.sort();
    lista5.display();
    std::cout<<"=====================list sorted previously after adding elements========================"<<std::endl;
    lista5.add_element(lista5.head, 2138);
    lista5.add_element(lista5.head->next, 2);
    lista5.display_val();
    std::cout<<"=================second sorting=================="<<std::endl;
    lista5.sort();
    lista5.display_val();
    lista5.serialization("C:\\Users\\ankat\\Desktop\\coding\\sem-3-project\\test.txt");
    List<int> lista6;
    lista6.deserialization("C:\\Users\\ankat\\Desktop\\coding\\sem-3-project\\test.txt");
    std::cout<<"================deserialization==================="<<std::endl;
    lista6.display_val();
    return 0;
}
