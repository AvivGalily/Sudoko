#include "trees.h"

void PlayInOrder(Tree tr, playerList* ActivePlayerlist)
{
    winnerList Winnerlist;


    makeEmptywinnerList(&Winnerlist);
    while (isEmptyPlayerList(*ActivePlayerlist) == false) { //if theres still players left , keep playing
        PlayInOrderHelper(tr.root, ActivePlayerlist, &Winnerlist);
    }
    if (isEmptywinnerList(Winnerlist) == true) {            // everyone lost
        printf("\n-----GAME OVER! everyone lost!-----\n");
        freePlayerList(*ActivePlayerlist);
    }
    else { // someone won, print the winners

        printf("\n");
        printf("\nGAME OVER!, the WINNER IS:\n");
        printwinnerList(&Winnerlist);
        freewinnerList(Winnerlist);
    }

}

void PlayInOrderHelper(TreeNode* root, playerList* ActivePlayerlist, winnerList* Winnerlist)
{
    int x = 0;
    int y = 0;

    playerListNode* arrycell;
    int status;
    if (root == NULL)
        return;
    else
    {
        PlayInOrderHelper(root->left, ActivePlayerlist, Winnerlist);
        if (root->data != NULL)
        {
            arrycell = *root->data;

            if (arrycell != NULL)
            {

                status = playTurn(arrycell->player);
                if (status == FINISH_FAILURE) { // removing the player from the list 
                    printf("player %s lost and is out of the game\n", arrycell->player->name);
                    freePlayer(arrycell);
                    removeplayerfromlist(ActivePlayerlist, arrycell);
                    root->data = NULL;
                }
                if (status == FINISH_SUCCESS) //player won: removing the player from active list, and inserts to winners list
                {
                    printf("player %s won and is out of the game\n", arrycell->player->name);
                    insertwinnerDataToEndList(Winnerlist, arrycell->player);
                    removeplayerfromlist(ActivePlayerlist, arrycell);
                    root->data = NULL;
                }
            }
        }
        PlayInOrderHelper(root->right, ActivePlayerlist, Winnerlist);
    }
}

Tree BuildTreeFromArray(playerListNode** arr, int  size) {
    int mid;
    Tree tr;
    Tree left; Tree right;
    tr.root = (TreeNode*)malloc(sizeof(TreeNode));
    checkMemoryAllocation(tr.root);
    if (size == 1)
    {
        tr.root->data = &arr[0];
        tr.root->left = NULL;
        tr.root->right = NULL;
    }
    else
    {
        mid = size / 2;
        tr.root->data = &arr[mid];

        left = BuildTreeFromArray(arr, mid);
        tr.root->left = left.root;
        right = BuildTreeFromArray(arr + mid + 1, mid);
        tr.root->right = right.root;

    }
    return tr;
}

void freeTree(Tree tr)
{
    freeTreeRec(tr.root);
}

void freeTreeRec(TreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        freeTreeRec(root->left);
        freeTreeRec(root->right);
        free(root);
    }
}