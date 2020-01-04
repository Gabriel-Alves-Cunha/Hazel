git status
git add *
git rm --cached Hazel/vendor/spdlog -f
git status
set /p msg="Write the commit message, please: "
git commit -m %msg% --date=rfc2822
git status
PAUSE