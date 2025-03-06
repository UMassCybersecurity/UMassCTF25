<p align="center">
  <img src="UMassCybersec.png" width="45%" style="margin-right: 15px;" />
  <img src="CTFd.png" width="45%" />
</p>

---
* [🚩 What is UMassCTFd?](#-UMassCtfd)
    + [📖 Overview](#-overview)
    + [🏗️ Architecture](#-architecture)
* [🚀 Quickstart - *for challenge authors*](#-quickstart)
    + [💻 Writing Challenges](#-writing-challs)
    + [🎉 Deploying Challenges](#-deploying-challs)
* [🛠️  Installation & Deployment - *for infra team*](#-deploy)
    + [1️⃣ Provision Cloud or On-Prem Services](#-provision)
    + [2️⃣  Setup CTFd](#-setup-ctfd)
    + [ 3️⃣ Configure Github Repo & Actions](#-github-repo)
---

## 🚩 What is UMassCTFd?  

UMassCTFd is an automated challenge + CTFd deployer used to provision and manage UMass Cybersecurity Club's CTFs and internal training platforms. 

###  📖 Overview

**Challenge Categories** <br>  
Each challenge category will have its own subdirectory under `/challenges`. All challenge directories must be placed in a subdirectory under `/challenges/${CATEGORY}`.

```
# Example Structure 
/challenges/
  ├── crypto/
  │    ├── challenge1/
  │    ├── challenge2/
  ├── web/
  │    ├── challenge1/
  │    ├── challenge2/
```

The categories are: 
-  🔐 crypto 
- 🔍 forensics 
-  🔌 hardware 
- 🎲 misc 
- 💣 pwn
- 🔄 rev 
-  🌐 web
- 🌍 OSINT 

> **INFO**
> To add a new category, you can just create a new subdirectory under `/challenges.` 

**Challenge Types** 

**Environments** 

**Environments** 

## 🚀 Quickstart 


## 🛠️  Installation & Deployment

### 1. Provision Cloud or On-Prem Services 
Challenges can be deployed on virtual machines hosted on a cloud platform or on-prem servers.  

<details>
  <summary><h4>GCP</h4></summary>

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

> [!NOTE]
> Woarkload Identity Federation is used to establish a trust delgation relationship between Github Actions workflow invocation and GCP permissions without storing service account keys to avoid long-lived credentials. 
> Definitions: 
> - Workload Identity Pool: "container" for external identities, groups multiple identity providers (ex. Github) and allows them to assume GCP IAM roles; the Workload Identity Pool will have direct IAM permissions on GCP resources.
> - Workload Identity Provider: specific OIDC identity source (ex. Github) within a Workload Identity Pool 

*6a. Create a Workload Identity Pool*
```sh 
# TODO: replace ${PROJECT_ID} with your value below.

gcloud iam workload-identity-pools create "github" \
  --project="${PROJECT_ID}" \
  --location="global" \
  --display-name="GitHub Actions Pool"
```

*6b. Get full ID of Workload Identity Pool* 
```sh
# TODO: replace ${PROJECT_ID} with your value below.

gcloud iam workload-identity-pools describe "github" \
  --project="${PROJECT_ID}" \
  --location="global" \
  --format="value(name)"

# value should be of format `projects/123456789/locations/global/workloadIdentityPools/github`
```

*6


</details>

<details>
  <summary><h4>Proxmox</h4></summary>
  This is the hidden content that appears when you click the summary.
</details>

### 2. Set up CTFd

### 3. Configure Github Repo &  Actions 
---
#TODO:
- squash commits
- why isnt [!NOTE] working?
- TODO: fix replacements in the workload identity provider
- make the workloa didentity provider steps a substep
