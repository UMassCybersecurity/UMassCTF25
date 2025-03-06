<p align="center">
  <img src="UMassCybersec.png" width="45%" style="margin-right: 15px;" />
  <img src="CTFd.png" width="45%" />
</p>

---
* [🚩 What is UMassCTFd?](#-UMassCtfd)
    + [✨ Features](#-features)
* [🚀 Quickstart](#-quickstart)
* [👩‍💻 Installation & Deployment](#-deploy)

---

## 🚩 What is UMassCTFd?  

UMassCTFd is an automated challenge + CTFd deployer used to provision and manage UMass Cybersecurity Club's CTFs and internal training platforms. 

### ✨Features 

## 🚀 Quickstart 


## 👩‍💻 Installation & Deployment

Challenges can be deployed on virtual machines hosted on a cloud platform or on-prem servers.  

<details>
  <summary><h3>GCP</h3></summary>

**1. Create a GCP Project**  
```sh
gcloud projects create PROJECT_ID --name="<PROJECT_NAME>"
```

**2. Authenticate with the GCP CLI**  
```sh
gcloud auth login
```
**3. Set GCP CLI project config**  
```sh
gcloud config set project <PROJECT_ID>
```

**4. Create a VM for each challenge category**  
```sh
for category in <CATEGORY_1 ... CATEGORY_N>; do
  gcloud compute instances create "${category}-challs" --zone=<ZONE> --machine-type=<MACHINE_TYPE>
done
```
*Example:* 
```sh
for category in web pwn misc; do
  gcloud compute instances create "${category}-challs" --zone=us-east1-b --machine-type=e2-medium
done
```

**5. Expose ports**  
```sh
gcloud compute firewall-rules create allow-http --allow=tcp:80
```
</details>

<details>
  <summary><h3>Proxmox</h3></summary>
  This is the hidden content that appears when you click the summary.
</details>

---
#TODO: make these expandable sections 

