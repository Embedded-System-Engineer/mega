import os
import subprocess
import json
import datetime

# Set project directory
PROJECT_DIR = os.path.dirname(os.path.abspath(__file__))
VERSION_FILE = os.path.join(PROJECT_DIR, "version.h")
VERSION_TRACKER_FILE = os.path.join(PROJECT_DIR, "branches_versions.json")  # Store branch versions

# Function to check if Git is initialized
def is_git_repository():
    return os.path.isdir(os.path.join(PROJECT_DIR, ".git"))

# Function to get the current Git remote URL
def get_git_remote():
    try:
        result = subprocess.run(["git", "remote", "get-url", "origin"], cwd=PROJECT_DIR, capture_output=True, text=True)
        return result.stdout.strip() if result.returncode == 0 else None
    except Exception:
        return None

# Function to set a remote URL if not exists
def set_git_remote():
    remote_url = get_git_remote()
    if not remote_url:
        remote_url = input("Enter your Git remote repository URL: ").strip()
        if remote_url:
            subprocess.run(["git", "remote", "add", "origin", remote_url], cwd=PROJECT_DIR)
            subprocess.run(["git", "add", "."], cwd=PROJECT_DIR)
            subprocess.run(["git", "commit", "-m", "first Commit"], cwd=PROJECT_DIR)
            subprocess.run(["git", "branch", "-M", "main"], cwd=PROJECT_DIR)
            subprocess.run(["git", "push", "-u", "origin", "main"], cwd=PROJECT_DIR)
            print(f"Remote repository set: {remote_url}")
        else:
            print("No remote URL entered. Exiting...")
            exit(1)

# Function to initialize Git if needed
def initialize_git():
    if not is_git_repository():
        print("Initializing new Git repository...")
        subprocess.run(["git", "init"], cwd=PROJECT_DIR)
    
    set_git_remote()

# Function to read branch versions from JSON
def read_branch_versions():
    if not os.path.exists(VERSION_TRACKER_FILE):
        return {}
    
    with open(VERSION_TRACKER_FILE, "r") as file:
        return json.load(file)

# Function to update branch versions in JSON
def update_branch_versions(branch_name, new_version):
    versions = read_branch_versions()
    versions[branch_name] = new_version  # Update version for the specific branch
    
    with open(VERSION_TRACKER_FILE, "w") as file:
        json.dump(versions, file, indent=4)

# Function to get last version for a branch
def get_last_version(branch_name):
    versions = read_branch_versions()
    return versions.get(branch_name, "1.0")  # Default to 1.0 if branch not found

# Function to get all branches
def get_all_branches():
    result = subprocess.run(["git", "branch", "-r"], cwd=PROJECT_DIR, capture_output=True, text=True)
    if result.returncode != 0:
        print("Error retrieving branches.")
        return []
    return [branch.strip().replace("origin/", "") for branch in result.stdout.splitlines()]

# Function to update the version in version.h
def update_version(branch_name):
    current_version = get_last_version(branch_name)
    major, minor = map(int, current_version.split("."))
    new_version = f"{major}.{minor + 1}"
    release_date = datetime.datetime.now().strftime("%d-%m-%Y")
    release_time = datetime.datetime.now().strftime("%H:%M:%S")
    
    update_branch_versions(branch_name, new_version)  # Store new version for the branch

    return new_version, release_date, release_time

# Function to update the version.h file with all branches and their version info
def update_version_header():
    branches = get_all_branches()
    current_branch = subprocess.run(["git", "rev-parse", "--abbrev-ref", "HEAD"], cwd=PROJECT_DIR, capture_output=True, text=True).stdout.strip()

    with open(VERSION_FILE, "w") as file:
        file.write('#ifndef VERSION_H\n#define VERSION_H\n')
        file.write(f'#define CURRENT_BRANCH "{current_branch}"\n')

        for branch in branches:
            new_version, release_date, release_time = update_version(branch)
            file.write(f'const char *{branch}_version[] = {{"version:{new_version}", "Date:{release_date}", "Time:{release_time}"}};\n')

        # Define the latest version for the current branch
        file.write(f'#define PROJECT_VERSION "{get_last_version(current_branch)}"\n')

        file.write('#endif')

    print(f"Updated version information for all branches in {VERSION_FILE}")

def branch_exists(branch_name):
    result = subprocess.run(["git", "branch"], cwd=PROJECT_DIR, capture_output=True, text=True)
    return branch_name in result.stdout

# Function to check if a remote branch exists
def remote_branch_exists(branch_name):
    result = subprocess.run(["git", "ls-remote", "--heads", "origin", branch_name], cwd=PROJECT_DIR, capture_output=True, text=True)
    return bool(result.stdout)  # If the output is non-empty, the branch exists

# Function to commit, pull from the remote branch, and push to the given branch
def git_commit_pull_and_push(branch_name, branch2_name):
    if not is_git_repository():
        print("Git repository not found.")
        initialize_git()
        return

    commit_message = f"Auto-update: Version update on branch {branch_name}"

    # Check if the branch exists locally
    if not branch_exists(branch_name):
        # Create and switch to the branch if it doesn't exist
        print(f"Branch {branch_name} not found. Creating and switching to it...")
        subprocess.run(["git", "checkout", "-b", branch_name], cwd=PROJECT_DIR)
    else:
        # Switch to the existing branch
        subprocess.run(["git", "checkout", branch_name], cwd=PROJECT_DIR)

    if branch2_name and remote_branch_exists(branch2_name):
        print(f"Pulling latest changes from remote branch {branch2_name}...")
        subprocess.run(["git", "fetch", "origin"], cwd=PROJECT_DIR)  # Fetch all remote branches
        subprocess.run(["git", "pull", "origin", branch2_name], cwd=PROJECT_DIR)  # Pull from branch2_name
    else:
        print(f"Skipping pull from {branch2_name} as it does not exist remotely or is not specified.")

    subprocess.run(["git", "add", VERSION_FILE, VERSION_TRACKER_FILE], cwd=PROJECT_DIR)
    subprocess.run(["git", "commit", "-m", commit_message], cwd=PROJECT_DIR)
    subprocess.run(["git", "push", "-u", "origin", branch_name], cwd=PROJECT_DIR)  # Push to specified branch

    print(f"Committed, pulled, and pushed to branch: {branch_name}")

# Function to keep the script running until manually closed
def keep_open():
    print("\nPress Ctrl+C to exit or close manually.")
    try:
        while True:
            pass
    except KeyboardInterrupt:
        print("\nExiting script.")

# Main execution
if __name__ == "__main__":
    initialize_git()  # Ensure Git is set up
    update_version_header()  # Update version header with all branches
    branch2 = input("Enter branch name to pull from: ").strip() or "main"  # Default to 'main' if empty
    branch = input("Enter branch name to push to: ").strip() or "main"  # Default to 'main' if empty
    git_commit_pull_and_push(branch, branch2)

    keep_open()  # Keep command window open
