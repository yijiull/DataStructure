struct rbNode{
   typedef rbNode* node_ptr;
   node_ptr parent, left, right;
   bool color;
   int val;
};