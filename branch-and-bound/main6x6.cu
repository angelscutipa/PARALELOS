#include <bits/stdc++.h> 
#include <iostream>
#include "instancias.cc"
#include <stdio.h>
#include <cuda_runtime.h>
#include <sys/time.h>
__global__
void vecAddKernel(int* costMatriz, bool *tempAllocated, bool *allocated, int minJob, int min, int imachine)
{
    int i = blockDim.x*blockIdx.x + threadIdx.x;
    if(!allocated[i] && tempAllocated[i] && costMatriz[i] < min) {
        minJob = i;
        min = costMatriz[i];
    }
}

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

        int calculateLeastCost(int costMatriz[6][6]) {
            int size = 6 * sizeof(int);
            int sizeb = 6 * sizeof(bool);
            int cost = 0;

            bool tempAllocated[this->problemSize] = {true};

            for(int imachine = this->machine+1; imachine < this->problemSize; imachine++) {
                int min = INT_MAX;
                int minJob = -1;
                /*  for(int ijob = 0; ijob < this->problemSize; ijob++) {
                    if(!allocated[ijob] && tempAllocated[ijob] && costMatriz[imachine][ijob] < min) {
                        minJob = ijob;
                        min = costMatriz[imachine][ijob];
                    }
                }  */

                int *d_A;
                bool *t_allocate, *t_allo;
                int *tminJob, *tmin, *tmachine;


                cudaMalloc((void **) &d_A, size);
                cudaMemcpy(d_A, costMatriz[imachine], size, cudaMemcpyHostToDevice);
                cudaMalloc((void **) &t_allocate, sizeb);
                cudaMemcpy(t_allocate, tempAllocated, sizeb, cudaMemcpyHostToDevice);
                cudaMalloc((void **) &t_allo, sizeb);
                cudaMemcpy(t_allo, allocated, sizeb, cudaMemcpyHostToDevice);

                vecAddKernel<<<ceil(6/256.00), 256>>>(d_A, t_allocate, t_allo, minJob, min, machine);

                cudaMemcpy(&minJob, tminJob, sizeof(int), cudaMemcpyDeviceToHost);
                cudaMemcpy(&min, tmin, sizeof(int), cudaMemcpyDeviceToHost);

                cost += min;
                tempAllocated[minJob] = false;

                cudaFree(d_A); cudaFree(t_allocate); cudaFree(tminJob); cudaFree(tmin); cudaFree(tmachine); cudaFree(t_allo);

                
            }

            return cost;
        } 
};



class BranchAndBound {
    public:
    
        BranchAndBound(int costMatriz[6][6]) {
            this->problemSize = 6;
            for(int i = 0; i < 6; i++) {
                for(int e = 0; e < 6; e++) {
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
        int costMatriz[6][6]; 

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


    BranchAndBound babP5(p8);
    babP5.minimumCostSearch();
    

    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
    printf("time bbRun 2:       %.28f s\n", tiempo/1000);

    return EXIT_SUCCESS;
}