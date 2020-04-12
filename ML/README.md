# HPC & BIG DATA - UvA 2020

Repository to host contents of the High Performance Machine Learning course within HPC & BIG DATA in 2020

![alt text](https://github.com/sara-nl/MLCourse/blob/master/cartesius.jpeg)

- If any problem persists, or you have a question you can send an email to:

rubenh@surfsara.nl | maxwell.cai@surfsara.nl  

# Setup

Start up a JupyterHub instance by going to the link:    
```
https://jupyter2.lisa.surfsara.nl/course
```
- Login with your username sdemoXXX and password
- Select the **UvA course** from the dropdown menu
- Wait for the server to be spawned...
- Good to go!

> We are going to use this JupyterHub instance on Lisa GPU for the practicals today. 

- Okay now, locate the dropdown button that says **New** in the top right corner, and start a Terminal window
> Now you are in your /home/sdemoXXX directory within the JupyterHub environment
- Run the command below to clone this git repository in your home directory:

```
git clone https://github.com/sara-nl/MLCourse.git
```
> This will clone the repository in your /home/sdemoXXX directory
- Go to the MLCourse directory and run install.sh by typing the following commands:
```
cd $HOME/MLCourse
sh install.sh
```
> Nice! We have installed the environment for today, so let's start a Jupyter Notebook
- Return to your **Home** tab and **refresh the page**, and start a Jupyter Notebook with the *UvA Course kernel* by selecting **UvA_Course** under **New** >> Notebook

> Check if everything is installed correctly by typing `import tensorflow as tf; print(tf.__version__)` in a cell, and then run the cell by pressing [SHIFT] [ENTER], it should output `1.15.0`



