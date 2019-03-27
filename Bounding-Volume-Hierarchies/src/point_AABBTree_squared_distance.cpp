#include "point_AABBTree_squared_distance.h"
#include "point_box_squared_distance.h"
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  // init priority queue based on min dist
  std::priority_queue<std::pair<double, std::shared_ptr<Object> >, std::vector<std::pair<double, std::shared_ptr<Object> > >, std::greater<std::pair<double, std::shared_ptr<Object> > > > Q;

  // insert distance to root box
  double dist = point_box_squared_distance(query, root->box);
  Q.push(std::pair<double, std::shared_ptr<Object> >(dist, root));

  // set max distance to check
  sqrd = max_sqrd;

  // breadth first search with queue
  while( !Q.empty() ){
    auto temp = Q.top();
    Q.pop();
    if(temp.first < sqrd && temp.first >= min_sqrd){
        auto node = std::dynamic_pointer_cast<AABBTree>(temp.second);
        if(node == nullptr){
            sqrd = std::min(sqrd,
                    point_box_squared_distance(query, temp.second->box));
            descendant = temp.second;
        }
        else{
            if(node->left != nullptr){
                Q.push(std::pair<double, std::shared_ptr<Object> > (
                             point_box_squared_distance(
                             query, node->left->box),
                             node->left));
            }
            if(node->right != nullptr){
                Q.push(std::pair<double, std::shared_ptr<Object> > (
                             point_box_squared_distance(
                             query, node->right->box),
                             node->right));
            }
        }
    }
  }
  if(sqrd >= max_sqrd) return false;
  return true;
}
