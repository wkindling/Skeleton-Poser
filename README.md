# Skeleton-Poser

Implementation of Skeleton animation and skinned mesh. 
This project is similar to https://github.com/alecjacobson/skeleton-poser. However, I don't use external library except Eigen. So you need not set a series of dependencies. 

The weights map is calculated by Bounded Biharmonic Weights based on Siggraph 2011. I use libigl library written by ETH Zurich to calculate the weights and visualize the model.  As for this part, you can see my another repository.

As for the structure of skeleton, BVH file format is referenced, whcih means that it can also support importing BVH file and play the animation. The skinned mesh method applied here is Linear Blending Skinning, so it will be easy for CUDA acceleration. And that is my following work.

Here is a simple gif which shows how to pose a big buck bunny. I have to say the bunny is so silly! lol
<img src="20190503_021217.gif" width="50%">


