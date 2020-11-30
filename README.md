# Vim configuration

Install Vundle
```
cd ~
mkdir -p .vim
cd .vim
mkdir -p bundle
cd bundle
git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
```

Install vimrc
```
cd ~
git clone https://github.com/aronfan/vimrc.git vimrc
echo "source ~/vimrc/vimrc.dev" > .vimrc
```

Install other plugins
```
vim
:PluginInstall
:qa
```

Compile the YCM
```
cd ~/.vim/bundle/YouCompleteMe
./install.py --clang-completer --go-completer
```

Install the YCM on ubuntu
```
sudo apt-get install vim-addon-manager
sudo apt-get install vim-youcompleteme
vim-addons install youcompleteme
```

Color
```
vim ~/.bashrc
[[ $TMUX = "" ]] && export TERM="xterm-256color"
```

```
vim ~/.tmux.conf
set -g default-terminal "screen-256color"
```

