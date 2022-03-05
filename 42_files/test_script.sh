apt-get install -y apt-utils
apt-get install -y nano
apt-get install -y wget
apt-get install -y nginx
apt-get install -y mariadb-server mariadb-client
apt-get install -y php-fpm php-mysql php-cli
apt-get install -y php-mbstring php-zip php-gd

./srcs/mysql_setup.sql /var/
chmod -R 755 /var/lib/mysql/
