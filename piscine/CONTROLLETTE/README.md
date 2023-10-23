# Controllette

# Result

- STATUS:GO : all ex* subdirectories have no extra files
apart from ft* files and contain at least one ft* file;
- STATUS:NO-GO : one or both of these conditions are not met.

# Usage

```
bash controllette.sh
```

# Final remarks
- The script creates, if necessary, a .gitignore and adds its original name and ".gitignore" to it;
- It also searches for unnecessary files in the root directory;
- Max depth is 1, in other words only the root and its ex* subdirectories are checked. Subdirectories of ex* subdirectories are ignored.
