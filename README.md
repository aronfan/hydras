# vim configuration

```
cd ~/.vim
mkdir bundle
cd bundle
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
vim
:PluginInstall
:qa
cd ~/.vim/bundle/YouCompleteMe
./install.py --clang-completer --go-completer
```
