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

**1. Create a GCP project**  
```sh
# TODO: replace ${PROJECT_NAME} with your GCP project name 

gcloud projects create PROJECT_ID --name="${PROJECT_NAME}"
```

**2. Authenticate with the GCP CLI**  
```sh
gcloud auth login
```
**3. Set GCP CLI project config**  
```sh
# TODO: replace ${PROJECT_ID} with your GCP project ID 

gcloud config set project ${PROJECT_ID}
```

**4. Create a VM for each challenge category**  
```sh
# TODO: replace ${CATEGORY_1} ${CATEGORY_2} ... ${CATEGORY_N} with your challenge categories; replace ${ZONE} and ${MACHINE_TYPE} with your GCP zone and Compute Engine machine type respectively 

for category in ${CATEGORY_1} ${CATEGORY_2} ${CATEGORY_N}; do
  gcloud compute instances create "${category}-challs" --zone=${ZONE} --machine-type=${MACHINE_TYPE}
done

# Example: 
# for category in web pwn misc; do
#   gcloud compute instances create "${category}-challs" --zone=us-east1-b --machine-type=e2-medium
# done
```

**5. Expose ports** #TODO 
```sh
gcloud compute firewall-rules create allow-http --allow=tcp:80
```
**6. Authenticate to GCP via Workload Identity Federation**

This [repo](https://github.com/google-github-actions/auth) has detailed documentation about Github Action authentication to GCP.

> [!Note]
> Woarkload Identity Federation is used to establish a trust delgation relationship between Github Actions workflow invocation and GCP permissions without storing service account keys to avoid long-lived credentials  

*6a. Create a Workload Identity Pool*
```sh 

```

</details>

<details>
  <summary><h3>Proxmox</h3></summary>
  This is the hidden content that appears when you click the summary.
</details>

---
#TODO:
- squash commits


