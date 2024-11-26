#ifndef AVLTREE_H
#define AVLTREE_H

#include "Song.h"
#include <iostream>

class AVLTree {
private:
    struct Node {
        Song song;
        Node* left;
        Node* right;
        int height;

        Node(const Song& s) : song(s), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, const Song& song) {
        if (!node) return new Node(song);
        if (song.getTrackName() < node->song.getTrackName())
            node->left = insert(node->left, song);
        else if (song.getTrackName() > node->song.getTrackName())
            node->right = insert(node->right, song);
        else
            return node;

        node->height = 1 + std::max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && song.getTrackName() < node->left->song.getTrackName())
            return rotateRight(node);
        if (balance < -1 && song.getTrackName() > node->right->song.getTrackName())
            return rotateLeft(node);
        if (balance > 1 && song.getTrackName() > node->left->song.getTrackName()) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && song.getTrackName() < node->right->song.getTrackName()) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const Song& song) {
        root = insert(root, song);
    }
};

#endif
