#include <stdio.h>
#include <stdbool.h>

int isMainGroup(int Graph[][7], int graph_N, int *Group, int group_M);
int isInGroup(int *Group, int group_M, int n);
int hasEdgeToGroup(int *connections, int numberOfConnections, int *Group, int group_M);

int main(){
    int Graph[][7] = {
        //   0  1  2  3  4  5  6
            {0, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 0, 1},
            {0, 1, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 1, 1},
            {0, 1, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 0}
    };
    int Group[] = {0,3,5};

    printf("the group {0,3,5} is%s a main group\n", isMainGroup(Graph,7,Group,3) ? "" : " not");
    return 0;
}


/*  input: graph and a group
 *  output: 1 if group is a "main group"
 *          0 otherwise.
 *
 *  a main group is defined to be a group
 *  of vertices that each of the vertices
 *  that aren't in the group have a connection
 *  to a vertices that is in the group
 *
 * */
int isMainGroup(int Graph[][7], int graph_N, int *Group, int group_M) {
    int i;

    for (i=0; i<graph_N; i++){
        /*  check if current node isn't in the group*/
        if (!isInGroup(Group, group_M,i)){
            /*  check if he has a connection to someone in the group    */
            if (!hasEdgeToGroup(Graph[i], graph_N, Group, group_M)){
                return 0;
            }
        }
    }

    return 1;
}

/*  input: a list of connections and a group.
 *  output: 1 if there is a connection to a vertices in the group
 *          0 otherwise
 * */
int hasEdgeToGroup(int *connections, int numberOfConnections, int *Group, int group_M) {
    int i;

    for (i=0; i<numberOfConnections; i++){
        if (connections[i] == 1 && isInGroup(Group,group_M,i)){
            return 1;
        }
    }
    return 0;
}

/*  input: group and a node number
 *  output: 1 if node is in group
 *          0 otherwise
 * */
int isInGroup(int *Group, int group_M, int n) {
    int i;


    for (i=0; i<group_M; i++){
        if (Group[i] == n){
            return 1;
        }
    }
    return 0;
}