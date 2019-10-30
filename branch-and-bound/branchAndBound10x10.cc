#include <bits/stdc++.h> 
#include <iostream>
#include "instancias.cc"
#include <sys/time.h>

class Node {
    public:
        Node(int machine, int job, bool* allocated, int problemSize, Node* parent = nullptr) {
            this->problemSize = problemSize;
            this->machine = machine;
            this->job = job;
            this->parent = parent;
            this->allocated = new bool[problemSize];


            for(int iallocated = 0; iallocated < this->problemSize; iallocated++) {
                this->allocated[iallocated] = allocated[iallocated];
            }
            this->allocated[this->job] = true;
        }

        int problemSize;
        int machine;
        int job;
        Node* parent;
        int pathCost;
        bool* allocated;
        int cost;

        int calculateLeastCost(int costMatriz[10][10]) {
            int cost = 0;

            bool tempAllocated[this->problemSize] = {true};

            for(int imachine = this->machine+1; imachine < this->problemSize; imachine++) {
                int min = INT_MAX;
                int minJob = -1;
                for(int ijob = 0; ijob < this->problemSize; ijob++) {
                    if(!allocated[ijob] && tempAllocated[ijob] && costMatriz[imachine][ijob] < min) {
                        minJob = ijob;
                        min = costMatriz[imachine][ijob];
                    }
                }

                cost += min;
                tempAllocated[minJob] = false;
            }

            return cost;
        } 
};

class BranchAndBound {
    public:
    
        BranchAndBound(int costMatriz[10][10]) {
            this->problemSize = 10;
            for(int i = 0; i < 10; i++) {
                for(int e = 0; e < 10; e++) {
                    this->costMatriz[i][e] = costMatriz[i][e];
                }
            }
        }

        int minimumCostSearch() {
            std::priority_queue<Node*, std::vector<Node*>, comp> queue;

            bool allocated[this->problemSize] = {false}; 
            Node* nodeZero = new Node(-1, -1, allocated, this->problemSize);
            nodeZero->pathCost = 0;
            nodeZero->cost = 0;
            nodeZero->machine = -1;

            queue.push(nodeZero);

            while(!queue.empty()) {
                Node* nodeMinCost = queue.top();
                queue.pop();
                int machine = nodeMinCost->machine + 1;

                if(machine == this->problemSize) {
                    printAssignments(nodeMinCost);
                    return nodeMinCost->cost;
                }

                for(int job = 0; job < this->problemSize; job++) {
                    if(!nodeMinCost->allocated[job]) {
                        Node* newNode = new Node(machine, job, nodeMinCost->allocated, this->problemSize, nodeMinCost);
                        newNode->pathCost = nodeMinCost->pathCost + costMatriz[machine][job];
                        newNode->cost = newNode->pathCost + newNode->calculateLeastCost(costMatriz);
                        queue.push(newNode);
                    }
                }
            }
        }

        void printAssignments(Node *min) { 
            if(min->parent==NULL) 
                return; 

            printAssignments(min->parent); 
            std::cout << "Assign Worker " << char(min->machine + 'A') 
                << " to Job " << min->job << std::endl; 
        } 

    private:

        int problemSize;
        int costMatriz[10][10]; 

        struct comp { 
            bool operator()(const Node* lhs, 
                        const Node* rhs) const
            { 
                return lhs->cost > rhs->cost; 
            } 
        };
};

int main() {

    struct timeval ti, tf;
    double tiempo;
    gettimeofday(&ti, NULL);

    BranchAndBound babP5(p5);
    babP5.minimumCostSearch();

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time bbRun 2:       %.28f s\n", tiempo/1000);
    
    std::cout << "-----------------------------------------------\n";


    return EXIT_SUCCESS;
}