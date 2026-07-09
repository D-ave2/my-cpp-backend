# Step 1: Use Ubuntu with Apache and G++
FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    apache2 \
    g++ \
    && rm -rf /var/lib/apt/lists/*

# Step 2: Explicitly unblock and activate the CGI configuration module
RUN a2enmod cgi

# Step 3: Tell Apache to grant full permission to execute our C++ scripts
RUN echo '<Directory "/usr/lib/cgi-bin">\n\
    AllowOverride None\n\
    Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch\n\
    Require all granted\n\
</Directory>' >> /etc/apache2/apache2.conf

# Step 4: Set our active working directory folder
WORKDIR /usr/lib/cgi-bin

# Step 5: Copy your backend C++ files down
COPY . .

# Step 6: Compile each C++ script into its own individual standalone app
RUN for file in *.cpp; do g++ -o "${file%.cpp}.cgi" "$file"; done

# Step 7: Fire up Apache
EXPOSE 80
CMD ["apachectl", "-D", "FOREGROUND"]
