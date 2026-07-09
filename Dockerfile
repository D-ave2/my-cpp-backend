# Step 1: Use an official Ubuntu image that includes Apache and G++
FROM ubuntu:latest

# Step 2: Install Apache server and C++ compiler tools quietly
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    apache2 \
    g++ \
    && rm -rf /lib/apt/lists/*

# Step 3: Enable the CGI module inside Apache so it can execute C++ programs
RUN a2enmod cgi

# Step 4: Set the working directory to Apache's CGI folder
WORKDIR /usr/lib/cgi-bin

# Step 5: Copy all your repository files into the CGI directory
COPY . .

# Step 6: Compile every single .cpp file into its own matching .cgi file automatically
RUN for file in *.cpp; do g++ -o "${file%.cpp}.cgi" "$file"; done

# Step 7: Configure Apache to run in the foreground and listen to Render's port
EXPOSE 80
CMD ["apachectl", "-D", "FOREGROUND"]
