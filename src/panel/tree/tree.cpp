#include "panel/tree/tree.hpp"

#include <algorithm>

std::shared_ptr<Tree::tnode> Tree::new_tnode(std::shared_ptr<tnode> parent_tnode, Panel& pl) {
    std::shared_ptr<tnode> _tnode(new tnode);
    _tnode->left = NULL;
    _tnode->right = NULL;
    _tnode->parent = parent_tnode;
    _tnode->pl = pl;
    return _tnode;
}

bool Tree::is_end_tnode(std::shared_ptr<tnode> _tnode) {
    if (_tnode->left == NULL && _tnode->right == NULL)
        return true;
    return false;
}

std::shared_ptr<Tree::tnode> Tree::find_tnode(Panel& pl) {
    for (auto next_tnode = tree_nodes.begin(); next_tnode != tree_nodes.end(); ++next_tnode)
        if ((*next_tnode)->pl == pl)
            return *next_tnode;
    return nullptr;
}

void Tree::remove_tnode(std::shared_ptr<tnode>& _tnode) {
    auto iter = std::find(tree_nodes.begin(), tree_nodes.end(), _tnode);
    tree_nodes.erase(iter);
    _tnode.reset();
}


void Tree::set_root(Panel& pl) { 
    tree_nodes.push_back( new_tnode(nullptr, pl) ); 
}

std::shared_ptr<Tree::tnode> Tree::get_root() { 
    return tree_nodes[0]; 
}

int Tree::get_count() { 
    return tree_nodes.size(); 
}

std::shared_ptr<Tree::tnode> Tree::find_parent(Panel& pl) { 
    return find_tnode(pl)->parent; 
}

void Tree::push_child(Panel& pl, Panel& pl1, Panel& pl2){
    std::shared_ptr<tnode>  _tnode = find_tnode(pl);
    tree_nodes.push_back( (_tnode->left = new_tnode(_tnode, pl1)) );
    tree_nodes.push_back( (_tnode->right = new_tnode(_tnode, pl2)) );
}

void Tree::get_childs(std::vector<Panel>& vec) {
    for (auto next_tnode = tree_nodes.begin(); next_tnode != tree_nodes.end(); ++next_tnode)
        if (is_end_tnode(*next_tnode))
            vec.push_back((*next_tnode)->pl);
}

void Tree::remove_childs(std::shared_ptr<tnode> _tnode) {
    if (!_tnode) 
        return;
    if (_tnode->left) {
        remove_childs(_tnode->left);
        remove_tnode(_tnode->left);
    }
    if (_tnode->right) {
        remove_childs(_tnode->right);
        remove_tnode(_tnode->right);
    }
} 