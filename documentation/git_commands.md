________________________________________________________

                    GIT COMMANDS
________________________________________________________

TERMINOLOGY

upstream: the original repo e.g, vedic-lang
origin: your fork of upstream e.g, SumeetSinghJi/vedic-lang

________________________________________________________

                FIRST TIME SETUP
________________________________________________________

Windows: https://git-scm.com/downloads
Mac: ```brew install git```
Linux: ```sudo apt install git```

Note: You will be asked to sign in web browser first time

```bash
git config --global user.name "Sumeet Singh"
git config --global user.email "sumeet.singhji@outlook.com"
```

________________________________________________________

                CREATE NEW REPO from CLI
________________________________________________________


Mac: brew install gh
2. ```gh auth login # follow setup steps```
3. ```gh repo create SumeetSinghJi/Heroes3MapLiker --public```

________________________________________________________

                FORK, CLONE, COMMIT, PUSH
________________________________________________________

```bash
#STEP 1 - FORK REPO
# e.g here click CREATE FORK: https://github.com/vedic-lang/vedic

#STEP 2 - CLONE REPO
git clone https://github.com/SumeetSinghJi/vedic
cd vedic
git remote add upstream https://github.com/vedic-lang/vedic

# STEP 3 - COMMIT/PUSH
git add .
git commit -m "Add your descriptive commit message here"
git push origin SUMEETS_BRANCH

# OPTIONAL - Safely reset last stage commit
git reset HEAD~1 # will remove last staged commit while not touching new code

# STEP 4A - NEW BRANCH
git branch # view local branches
git branch -r # view remote branches
git branch -D 2.0.6_vedic_formula # delete branch
git push origin --delete 2.0.6_vedic_formula # delete remote branch
git fetch --prune # sync your origin
git branch -r # view remote branches
git checkout -b SUMEETS_BRANCH # create a new branch

# STEP 4B - SHARED BRANCH
git pull --rebase # sync your local branch with latest updates
git rebase --abort # if there are merge conflicts then abort to pull normally
git pull # merge your commits with the latest online branch

# STEP 5 - PULL REQUEST
# Go to your forked repo and click COMPARE PULL REQUEST and accept

# STEP 6 - SYNC FORK
git remote -v
git remote remove origin # optional to delete wrong remote
git remote add upstream https://github.com/vedic-lang/vedic
git fetch upstream
git merge upstream/main
git reset --hard upstream/main
```


________________________________________________________

            BREW FORMULA COMMIT WORKFLOW
________________________________________________________

```bash
# STEP 1 - FORK REPO
# e.g here click CREATE FORK: https://github.com/Homebrew/homebrew-core
brew tap --force homebrew/core
cd "$(brew --repository homebrew/core)"
cp ~/Documents/homebrew-vedic/vedic.rb Formula/v # copy your formula to your local brew for testing
cd Formula/v

# STEP 2 - TEST INSTALL OF FORMULA
HOMEBREW_VERBOSE=1 HOMEBREW_NO_AUTO_UPDATE=1 brew reinstall --build-from-source vedic.rb
# if above command fails to install or you get an error, run bellow CLEANUP step to uninstall and try again

# OPTIONAL STEP - CLEANUP
brew uninstall vedic
brew cleanup vedic
brew cleanup --prune=all
rm -rf $(brew --cache)/*
rm -rf $(brew --repository)/Library/Logs/Homebrew/*

# STEP 3 - RUN TESTS
# NOTE: If you get error wrong constant name, reading as formulae not brew
# or error cannot read from source, ignore. These are auto fixed when formulae
# is accepted, homebrew bot will add bottle data to the formula to fix
brew test vedic
brew audit --strict --online vedic
brew audit --new vedic
brew style --fix vedic
# if fails run CLEANUP STEP and try again

# OPTIONAL - IF FILE MODIFIED IN WINDOWS
sed -i '' 's/\r//' /Users/sumeetsingh/Documents/homebrew-vedic/vedic.rb # removes higgen carraige returns text from file
chmod +x vedic.rb # give all write access to run on macos/unix like machines

# STEP 4 - COMMIT PUSH
cp ~/Documents/homebrew-vedic/vedic.rb ~/Documents/homebrew-core/Formula/v
cd ~/Documents/homebrew-core
git remote add SumeetSinghJi https://github.com/SumeetSinghJi/homebrew-core.git
git checkout -b 2.0.6-vedic-new-formula origin/master
git add Formula/v/vedic.rb
git commit -m "vedic 2.0.6: add new formula

This formula installs the Vedic package for version 2.0.6."
git push --set-upstream SumeetSinghJi 2.0.6-vedic-new-formula

# STEP 5 - CLEANUP
brew untap homebrew/core # revert environment to default

# STEP 6 - Go to upstream repo on Github.com and you can see a new Pull request has been created
# if there are any issues you will be notified by an admin to fix, and when you approve code changes
# it will auto merge
```