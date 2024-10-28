# Beginner's Guide to Working with Git: Cloning, Adding, Committing, and Pushing

This guide will walk you through the basics of Git: cloning a repository, 
adding changes, committing, pushing, and checking the status of your work. 
These steps will help you start contributing to the project 
after being added as a collaborator. 

## Steps to Get Started
### 1. Cloning the Repository

Cloning creates a local copy of the repository on your computer, so you can start making changes.

1. Navigate to the repository on GitHub.

2. Click on the green "Code" button and copy the HTTPS link.

3. In your terminal, run the following command (replace <repository-URL> with the copied link):

```bash
git clone <repository-URL>
```
Example Output:

```bash
Cloning into 'project-name'...
remote: Enumerating objects: 10, done.
remote: Counting objects: 100% (10/10), done.
Receiving objects: 100% (10/10), done.
```

Now, you'll have a local copy of the repository on your computer.

### 2. Checking the Status of Your Work

To see if there are any changes in your local repository
that haven’t been staged, committed, or pushed, use:

```bash
git status
```

Example Output:

```bash
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

This output means that no changes have been made since the last commit.

### 3. Making and Staging Changes

When you make changes to files, they’ll appear as “modified” in Git. 
To stage changes (prepare them to be committed), use:

```bash
git add .
```
Result: Running this command stages all the changed files, 
preparing them for a commit. To see the status after staging:

```bash
git status
```

Example Output:

```bash
Changes to be committed:
(use "git restore --staged <file>..." to unstage)
modified:   filename.txt
```

### 4. Committing Changes

Committing saves your staged changes with a message describing what you did.

```bash
git commit -m "Descriptive message about changes"
```

Example:

```bash
git commit -m "Added new feature for processing data"
```

Result:

```bash
[main 1a2b3c4] Added new feature for processing data
1 file changed, 10 insertions(+)
```

### 5. Pushing Changes to GitHub

To upload your committed changes to the repository on GitHub, use:

```bash
git push origin your_branch
```
Example Output:

```bash
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 8 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 4.10 KiB | 1.02 MiB/s, done.
Total 3 (delta 2), reused 0 (delta 0)
To github.com:username/repo.git
```
After pushing, your changes will be visible on GitHub in your branch.