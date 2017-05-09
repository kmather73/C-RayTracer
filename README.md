# Recursive RayTracer in C++ and OpenMP

I have implemented a recursive ray tracer that uses a [phong illumination model](https://en.wikipedia.org/wiki/Phong_reflection_model) with multiple lights sources, distance attenuation, refractions, and  shadows. The antialiasing method used is stochastic supersampling from a 2D Normal distribution. Inorder to speed things up I used a [k-d Tree](https://en.wikipedia.org/wiki/K-d_tree) as an acceleration data structure as well as [OpenMP](https://en.wikipedia.org/wiki/OpenMP) for multi-threading, note you may need to [enable](https://msdn.microsoft.com/en-us/library/fw509c3b.aspx) OpenMP in Visual Studio to take advantage of multiple cores.


## Dependencies
Inorder to compile the code you first need to unzip the `fltk-1.3.3.7z` file into the root of the project. Then open the `ray.sln` file and make the project.  There is a preexisting ray.exe file in the `Release` folder that you can use, it may or may not work for you with out compiling the project.



[image1]: ./Images/balls.png
[image2]: ./Images/balls2.png
[image3]: ./Images/balls3.png
[image4]: ./Images/balls4.png
[image5]: ./Images/balls5.png
[image6]: ./Images/balls6.png
[image7]: ./Images/box.png
[image8]: ./Images/box-cyl.png
[image9]: ./Images/cone.png
[image10]: ./Images/hand.png
[image11]: ./Images/knight.png
[image12]: ./Images/things-inside-things.png

## Rendered Images
Here are some example of scenes rendered by the raytracer
![alt text][image6]
![alt text][image1]
![alt text][image11]
![alt text][image2]
![alt text][image4]
![alt text][image5]
![alt text][image7]
![alt text][image8]
![alt text][image12]
![alt text][image9]
![alt text][image10]
![alt text][image3]

