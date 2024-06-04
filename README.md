### AVL Tree
The avl_tree class is a simple avl tree implementation that utilizes recursive
functions to insert and delete nodes.

Rotation of the nodes is based on their balance factor, which is not stored in
the node itself, but rather calculated when rebalancing. Nodes only store: key,
left child, right child, parent, and height. Additional values can be added to
the node struct for functionality, but the four variables should **not** be messed
with.

If there are any problems please tell me! This is my first time implementing
something like this and did not test the implementation extensively!!
