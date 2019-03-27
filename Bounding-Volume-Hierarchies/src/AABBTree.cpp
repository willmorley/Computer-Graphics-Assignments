#include "AABBTree.h"
#include "insert_box_into_box.h"
#include "ray_intersect_box.h"
#include <iostream>
#include <algorithm>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth):
  depth(std::move(a_depth)),
  num_leaves(objects.size())
{
  if(num_leaves == 1){ //consider N == 0??
    this->left = objects[0];
    this->right = nullptr;
    insert_box_into_box(objects[0]->box, this->box);
    //insert_triangle_into_box(
        //V.row(F(f,0)),
        //V.row(F(f,1)),
        //V.row(F(f,2)),
        //box);
  }
  else if(num_leaves == 2){
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
  }
  else{
    // Sort objects by center point around longest axis
    // 1. Find longest axis
    int axis = 0;
    auto compare = [&axis](const std::shared_ptr<Object> &a,
                            const std::shared_ptr<Object> &b)
    {
            return(a->box.center()[axis] < b->box.center()[axis]);
    };

    auto x_max = std::max_element(objects.begin(), objects.end(), compare);
    auto x_min = std::min_element(objects.begin(), objects.end(), compare);
    double x_diff = std::abs((*x_max)->box.center()[0] - (*x_min)->box.center()[0]);

    axis++;

    auto y_max = std::max_element(objects.begin(), objects.end(), compare);
    auto y_min = std::min_element(objects.begin(), objects.end(), compare);
    double y_diff = std::abs((*y_max)->box.center()[1] - (*y_min)->box.center()[1]);

    axis++;

    auto z_max = std::max_element(objects.begin(), objects.end(), compare);
    auto z_min = std::min_element(objects.begin(), objects.end(), compare);
    double z_diff = std::abs((*z_max)->box.center()[2] - (*z_min)->box.center()[2]);

    std::vector<double> diffs {x_diff, y_diff, z_diff};
    axis = std::max_element(diffs.begin(), diffs.end()) - diffs.begin();


    // 2. sort boxes by center point along that axis
    auto new_objects(objects);
    std::sort(new_objects.begin(), new_objects.end(), compare);

    // Recursively create subtrees
    auto start = new_objects.begin();
    this->left = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(start, start + (num_leaves/2)), depth + 1);
    this->right = std::make_shared<AABBTree>(std::vector<std::shared_ptr<Object>>(start + (num_leaves/2), new_objects.end()), depth + 1);

    // Resize box
    insert_box_into_box(this->left->box, this->box);
    insert_box_into_box(this->right->box, this->box);
  }
}

bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const
{
  if(ray_intersect_box(
                ray,
                this->box,
                min_t,
                max_t))
  {
    //descendant = std::static_pointer_cast<Object>(this);
    std::shared_ptr<Object> l_desc = this->left;
    std::shared_ptr<Object> r_desc = this->right;
    double l_t, r_t;

    // check left subtree
    bool l_hit = this->left ? this->left->ray_intersect(ray, min_t, max_t, l_t, l_desc) : false;
    // check right subtree
    bool r_hit = this->right ? this->right->ray_intersect(ray, min_t, max_t, r_t, r_desc) : false;

    // take min of two t's
    if(l_hit && r_hit){
        t = l_t < r_t ? l_t : r_t;
        descendant = l_t < r_t ? l_desc : r_desc;
        return true;
    }
    else if(l_hit || r_hit){
        t = l_hit ? l_t : r_t;
        descendant = l_hit ? l_desc : r_desc;
        return true;
    }
  }
  t = 0;
  return false;
}
