git reflog expire --expire=now --all
git gc --prune=now --aggressive
git push origin main --force
