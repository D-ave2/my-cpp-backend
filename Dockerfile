# Step 1: Use an official GCC image to compile your C++ code
FROM gcc:latest

# Step 2: Create a working directory inside the cloud container
WORKDIR /usr/src/app

# Step 3: Copy all your local backend files into the cloud container
COPY . .

# Step 4: Compile your C++ code into an executable named "myserver"
# (Change main.cpp if your main file has a different name)
RUN g++ -o myserver main.cpp

# Step 5: Tell the container to expose the port your server listens to
EXPOSE 8080

# Step 6: Command to run your compiled server
CMD ["./myserver"]
