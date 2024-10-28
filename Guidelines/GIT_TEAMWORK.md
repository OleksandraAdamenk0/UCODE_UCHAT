# Guide to Working with Git and GitHub in a Team

Key principles for using Git and GitHub to address typical issues
and conflicts in collaborative project work.

## Core Principles 

### Syncing with the Remote Repository
Always start by syncing your local repository with the remote repository using:

```bash
git pull origin main
```

This command ensures your local code is up-to-date and avoids conflicts
with the latest changes.

### Creating New Branches

For each new feature or change, create a new branch
to keep the main branch stable. Use:

```bash
git checkout -b branch-name
```
### Making Changes and Committing

Make changes on the new branch, stage them, and commit:

```bash
git add .
git commit -m "Fixed memory leaks in function_name."
```

**Result:**

```bash
[branch-name 1a2b3c4] Fixed memory leaks in function_name.
1 file changed, 10 insertions(+), 0 deletions(-)
```

### Pushing Changes to the Remote Repository

After making changes in your local branch, push them to the pre-existing branch
in the remote repository for the current change.

```bash
git push origin branch-name
```

Successful output:

```bash
user@maschine:~/path/UCODE_UCHAT$ git push origin feature-1
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 8 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 4.10 KiB | 1.02 MiB/s, done.
Total 3 (delta 2), reused 0 (delta 0)
To github.com:username/repo.git
a1b2c3d..e4f5g6h  feature-1 -> feature-1
```

### Go to GitHub and Create a Pull Request

Click the "Compare & pull request" button on the main page.

**!!! Pay attention to the branch name. Only create pull requests for your own branches**

![Screenshot showing button location](Assets/main_page_pull_request_btn.jpg)

Or, switch from main to your own branch and click "pull request"
in the prompt in your branch.

![Screenshot showing button location](Assets/pull_request_btn.jpg)

Opening a pull request:

![Screenshot of pullrequest menu](Assets/pull_request_comment.jpg)
