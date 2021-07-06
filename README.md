# sorting-visualized
Visualization of sorting algorithms made in C++11 with SDL 1.2.14

The showcased sorting algorithms in order:
-Selection sort
-Insertion sort
-Quick sort
-Shell sort
-std::sort
-std::stable_sort

Once an algorithm finishes you can advance by pressing the left mouse button.
If you click outside of the window while it's running then the animation can become unstable.

I made this for a university course back in 2017. All the comments in the code are in Hungarian.

The main highlight of this program is that we store the values in our custom Drawable objects and they draw themselves automatically.
You can use the sortingdraw.hpp for any kind of data visualizations using the Drawable and DrawableList classes.
