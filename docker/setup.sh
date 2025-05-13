#!/bin/bash

# Make sure Docker is running
docker info > /dev/null 2>&1
if [ $? -ne 0 ]; then
  echo "Error: Docker is not running. Please start Docker and try again."
  exit 1
fi

# Create database initialization directory if it doesn't exist
mkdir -p db-init

# Create SQL initialization script if it doesn't exist
if [ ! -f db-init/init.sql ]; then
  cat > db-init/init.sql << 'EOF'
-- Create tables for the payment system
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL,
    email VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS wallets (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL,
    balance DECIMAL(10, 2) DEFAULT 0.00,
    currency VARCHAR(3) DEFAULT 'USD',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE IF NOT EXISTS transactions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    sender_wallet_id INT NOT NULL,
    receiver_wallet_id INT NOT NULL,
    amount DECIMAL(10, 2) NOT NULL,
    description TEXT,
    transaction_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (sender_wallet_id) REFERENCES wallets(id),
    FOREIGN KEY (receiver_wallet_id) REFERENCES wallets(id)
);

-- Insert some sample data
INSERT INTO users (username, password, email) VALUES
    ('john_doe', 'password123', 'john@example.com'),
    ('jane_smith', 'password456', 'jane@example.com');

INSERT INTO wallets (user_id, balance, currency) VALUES
    (1, 1000.00, 'USD'),
    (2, 500.00, 'USD');

INSERT INTO transactions (sender_wallet_id, receiver_wallet_id, amount, description) VALUES
    (1, 2, 100.00, 'Payment for services');
EOF
  echo "Created database initialization script in db-init/init.sql"
fi

# Create a sample database.conf file if it doesn't exist
mkdir -p config
if [ ! -f config/database.conf ]; then
  cat > config/database.conf << 'EOF'
host=mysql
port=33060
database=payment_system
user=payment_user
password=payment_password
EOF
  echo "Created database configuration file in config/database.conf"
fi

# Start the development environment
echo "Starting development environment..."
docker-compose up -d mysql
echo "MySQL has been started. Waiting for it to initialize..."
sleep 10

echo "Starting the development container..."
docker-compose up -d app-dev

echo "Development environment is now running."
echo "To build and run the application, execute:"
echo "docker-compose exec app-dev bash"
echo "Then, inside the container:"
echo "mkdir -p build && cd build && cmake .. && make && ./bin/payment-system"

echo ""
echo "To stop the environment, run: docker-compose down"