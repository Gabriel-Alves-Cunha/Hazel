@echo off
git status
set /p branch="What is the name of this branch? COPY AND PASTE IT FROM ABOVE: "
git add *
git rm --cached Hazel/vendor/spdlog -f
git status
set /p msg="Write the commit message, please: "
git commit -m "%msg%" --date=rfc2822
git status
git pull origin %branch%
git push
cmd /k

PAUSE