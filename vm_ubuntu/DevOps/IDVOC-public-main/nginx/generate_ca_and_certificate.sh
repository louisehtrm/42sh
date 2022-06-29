echo "authorityKeyIdentifier=keyid,issuer
basicConstraints=CA:FALSE
keyUsage = digitalSignature, keyEncipherment
subjectAltName = @alt_names

[alt_names]
DNS.1 = net2.example.org
DNS.2 = *.net2.example.org" > net2.example.org.ext

# CREATING A CA

# create a certificate and self-sign it
openssl req -x509 -new -nodes -newkey rsa:2048 -keyout ca.key -sha256 -days 2048 -out ca.crt -subj "/C=FR/ST=GRAND-EST/L=STRASBOURG/O=EPITA/OU=NET2/CN=NET2"

# CREATING A CERTIFICATE FOR A DOMAIN

#create a CSR
openssl req -nodes -new -newkey rsa:2048 -keyout net2.example.org.key -out net2.example.org.csr -subj "/C=FR/ST=GRAND-EST/L=STRASBOURG/O=EPITA/OU=NET2/CN=net2.example.org"

# CREATE THE CERTIFICATE WITH THE CA ROOT KEY

openssl x509 -req -in net2.example.org.csr -CA ca.crt -CAkey ca.key -CAcreateserial -out net2.example.org.crt -days 365 -sha256 -extfile net2.example.org.ext