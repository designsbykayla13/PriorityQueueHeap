// FILE: pqueue2.cxx
// IMPLEMENTS: PriorityQueue (See pqueue2.h for documentation.)
// IMPLEMENTED BY: (name and email address)
//
// NOTE: You will need -lm at the end of your compile line to pick up
// the math library!

// INVARIANT for the PriorityQueue Class:
//   1. The member variable many_items is the number of items in the
//      PriorityQueue.
//   2. The items themselves are stored in the member variable heap,
//      which is a partially filled array organized to follow the usual
//      heap storage rules from Chapter 11 of the class notes.
// NOTE: Private helper functions are implemented at the bottom of this
// file along with their precondition/postcondition contracts.
 
#include <cassert>    // Provides assert function
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <cmath>      // Provides log2
#include "pqueue2.h"
using namespace std;

PriorityQueue::PriorityQueue( )
{
    many_items = 0; 
    return;
    // -- Student will implement this.
}

void PriorityQueue::insert(const Item& entry, unsigned int priority)
{
    // -- Student will implement this.
    heap[many_items].data = entry;
    heap[many_items].priority = priority;
    ++many_items;
    if(many_items==1){
        return;
    }
    else{
        size_t follow = many_items-1; //last index
        while (follow != 0 && (parent_priority(follow)<heap[follow].priority) ) {
             size_t swap = parent_index(follow);
            swap_with_parent(follow);
            follow = swap;
        }
        return;
    }
    
}

PriorityQueue::Item PriorityQueue::get_front( )
{
    // -- Student will implement this.
    assert(size()>0);
    Item rootValue = heap[0].data;
    --many_items;
    if(many_items > 0){
        heap[0] = heap[many_items];
        size_t follow = 0;
        while (!is_leaf(follow) && heap[follow].priority<big_child_priority(follow)) {
            follow = big_child_index(follow);
            swap_with_parent(follow);
        }
    }
    return rootValue;
}

bool PriorityQueue::is_leaf(size_t i) const
// Precondition: (i < many_items)
// Postcondition: If heap[i] has no children in the heap, then the function
// returns true. Otherwise the function returns false.
{
    // -- Student will implement this.
    assert(i<many_items);
    if((2*i)+1 > many_items && (2*i)+2 > many_items){
        return true;
    }
    return false;
    
}

size_t PriorityQueue::parent_index(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the index of the parent of heap[i].
{
    // -- Student will implement this.
    assert((i>0) && (i<many_items));
    return ((i-1)/2);
    
}

unsigned int PriorityQueue::parent_priority(size_t i) const
// Precondition: (i > 0) && (i < many_items)
// Postcondition: The return value is the priority of the parent of heap[i].
{
    // -- Student will implement this.
    assert((i>0) && (i<many_items));
    return heap[parent_index(i)].priority;
    
}

size_t PriorityQueue::big_child_index(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value is the index of one of heap[i]'s children.
// This is the child with the larger priority.
{
    // -- Student will implement this.
    assert(!is_leaf(i));
    size_t big_child;
    if((2*i+2)==many_items){
        big_child = 2*i+1;
    }
    else if(heap[2*i+1].priority > heap[2*i+2].priority)
        big_child = 2*i+1;
    else
        big_child = 2*i+2;
    return big_child;
    
}

unsigned int PriorityQueue::big_child_priority(size_t i) const
// Precondition: !is_leaf(i)
// Postcondition: The return value heap[big_child_index(i)].priority
{
    // -- Student will implement this.
    assert(!is_leaf(i));
    return heap[big_child_index(i)].priority;
    
}

void PriorityQueue::swap_with_parent(size_t i)
// Precondition: (i > 0) && (i < many_items)
// Postcondition: heap[i] has been swapped with heap[parent_index(i)]
{
    // -- Student will implement this.
    assert((i > 0) && (i < many_items));
    Item swapData = heap[i].data;
    unsigned int swapPriority = heap[i].priority;
    heap[i] = heap[parent_index(i)];
    heap[parent_index(i)].data = swapData;
    heap[parent_index(i)].priority = swapPriority;
    return;
    
}

void PriorityQueue::print_tree(const char message[ ], size_t i) const
// Postcondition: If the message is non-empty, then that has been written
// to cout. After the message, the portion of the heap with root at node
// node i has been written to the screen. Each node's data is indented
// 4*d, where d is the depth of the node.
// NOTE: The default argument for message is the empty string, and the
// default argument for i is zero. For example, to print the entire
// tree of a PriorityQueue p, with a message of "The tree:", you can call:
//     p.print_tree("The tree:");
// This call uses the default argument i=0, which prints the whole tree.
{
    const char NO_MESSAGE[ ] = "";
    size_t depth;

    if (message[0] != '\0')
        cout << message << endl;

    if (i >= many_items)
        cout << "NO NODES." << endl;
    else
    {
        depth = int(log(double(i+1))/log(2.0));
        cout << setw(depth*4) << "";
        cout << heap[i].data;
        cout << " (priority " << heap[i].priority << ")" << endl;
        if (2*i + 1 < many_items)
            print_tree(NO_MESSAGE, 2*i + 1);
        if (2*i + 2 < many_items)
            print_tree(NO_MESSAGE, 2*i + 2);
    }
}
