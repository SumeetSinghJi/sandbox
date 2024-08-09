
# PROGRAMMING WITH RUBY

By: Sumeet Singh @ sumeet-singh.com

Date: July 2024

# TABLE OF CONTENTS
- [1. Terminologies](#terminologies)
- [2. Requirements](#requirements)
- [3. Installing](#installing)
- [4. Profile script](#profile-script)
- [5. Common Commands](#common-commands)
- [6. Scripts](#scripts)
- [7. Jekyll](#jekyll)

# TERMINOLOGIES

# REQUIREMENTS

# INSTALLING

1. INSTALLING RUBY

NOTE: on MacOS ruby comes preinstalled, however it's being phased out and is often out of date so it's best to install latest version manually
Windows: https://www.ruby-lang.org/en/documentation/installation/
MacOS: ```brew install ruby```
Linux: ```apt install ruby```

2. ADD TO ENVIRONMENTAL VARIABLES (IF NOT AUTOMATIC)

WINDOWS: Should be automatic test step 3. on failure check program files folder add /bin path to environmental variables

LINUX/MACOS
2a. FIND RUBY BIN PATH
```bash
which ruby
#or
where ruby

sumeetsingh@Sumeets-Air-2 sandbox % where ruby
/opt/homebrew/Cellar/ruby/3.3.2/bin/ruby
/usr/bin/ruby
```
2b. ADD ENVIRONEMNTAL VARIABLE TO SHELL
There are 3 or more shell's usually e.g, ~/.zshrc, ~/.bash or ~/.bash_profile.
edit 1 to include the envionmental variable as per below steps, and remove any outdated version
form the other shell scripts
for MacOS add the path only to: ~/.zshrc

EXAMPLE

```bash
sumeetsingh@Sumeets-Air-2 sandbox % cat ~/.zshrc   \
export PATH="/opt/homebrew/Cellar/ruby/3.3.2/bin:$PATH" # from brew install ruby
```

3. VERIFY RUBY
if your unsure if the version output is correct you can check the package manager to compare versions e.g.
brew info ruby
apt search ruby
```bash
ruby --version
```
EXAMPLE
```bash
sumeetsingh@Sumeets-Air-2 ~ % ruby --version
ruby 3.3.2 (2024-05-30 revision e5a195edf6) [arm64-darwin23]
```

4. INSTALL GEMS
```bash
gem install jekyll
```

5. VIEW INSTALLED GEMS
```bash
gem list
```

EXAMPLE
```bash
sumeetsingh@Sumeets-Air-2 vedic-lang.github.io % gem list                  

*** LOCAL GEMS ***

jekyll (0.9.1)
```

# PROFILE SCRIPT

# COMMON COMMANDS

# SCRIPTS

# JEKYLL

Jekyll is a static website generator

1. INSTALL JECKYLL AND DEPENDENCIES

```bash
gem install jekyll bundlerr
```

2. TEST SITE
```bash
cd xxxxx # change directory to the cloned repo then run below
bundle exec jekyll serve
```
