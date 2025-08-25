#include "panel/panel.hpp"

#include <memory>
#include <vector>

class Tree {
private:
    
    class tnode {
    public:
        Panel pl;
        std::shared_ptr<tnode> left;
        std::shared_ptr<tnode> right;
        std::shared_ptr<tnode> parent;
    };

    std::vector<std::shared_ptr<tnode>> tree_nodes;

    std::shared_ptr<tnode> new_tnode(std::shared_ptr<tnode> parent_tnode, Panel& pl);

    bool is_end_tnode(std::shared_ptr<tnode> _tnode);

    std::shared_ptr<tnode> find_tnode(Panel& pl);

    void remove_tnode(std::shared_ptr<tnode>& _tnode);
    
public:

    void set_root(Panel& pl);
    std::shared_ptr<tnode> get_root();
    int get_count();
    std::shared_ptr<tnode> find_parent(Panel& pl);

    void push_child(Panel& pl, Panel& pl1, Panel& pl2);

    void get_childs(std::vector<Panel>& vec);

    void remove_childs(std::shared_ptr<tnode> _tnode);
};