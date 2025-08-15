#include "panel/panel.hpp"

#include <vector>
#include <algorithm>
#include <memory>

class Tree {
private:
    
    class tnode {
    public:
        Panel pl;
        std::shared_ptr<tnode> left;
        std::shared_ptr<tnode> right;
    };

    std::vector<std::shared_ptr<tnode>> tree_nodes;

    std::shared_ptr<tnode> new_tnode(Panel& pl) {
        std::shared_ptr<tnode> _tnode(new tnode);
        _tnode->left = NULL;
        _tnode->right = NULL;
        _tnode->pl = pl;
        return _tnode;
    }

    bool is_end_tnode(std::shared_ptr<tnode> _tnode) {
        if (_tnode->left == NULL && _tnode->right == NULL)
            return true;
        return false;
    }

    std::shared_ptr<tnode>  find_tnode(int id) {
        for (auto next_tnode : tree_nodes)
            if (next_tnode->pl.get_id() == id)
                return next_tnode;
        return nullptr;
    }

    void remove_tnode(std::shared_ptr<tnode>& _tnode) {
        auto iter = std::find(tree_nodes.begin(), tree_nodes.end(), _tnode);
        tree_nodes.erase(iter);
        _tnode.reset();
    }
    
public:

    void set_root(Panel& pl) {
        tree_nodes.push_back(new_tnode(pl));
    }

    void push_child(int pid, Panel& pl1, Panel& pl2){
        std::shared_ptr<tnode>  _tnode = find_tnode(pid);
        tree_nodes.push_back((_tnode->left = new_tnode(pl1)));
        tree_nodes.push_back((_tnode->right = new_tnode(pl2)));
    }

    void get_child(std::vector<Panel>& vec) {
        for (auto next_tnode : tree_nodes)
            if (is_end_tnode(next_tnode))
                vec.push_back(next_tnode->pl);
    }

    void remove_childs(Panel& pl) {
        auto _tnode = find_tnode(pl.get_id());
        if (!_tnode) 
            return;

        if (_tnode->left) {
            remove_childs(_tnode->left->pl);
            remove_tnode(_tnode->left);
        }
        if (_tnode->right) {
            remove_childs(_tnode->right->pl);
            remove_tnode(_tnode->right);
        }

        
    }

    std::shared_ptr<tnode>  get_root() { return tree_nodes[0]; }
    int get_count() { return tree_nodes.size(); }
    
};