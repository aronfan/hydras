# Vim Configuration

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
mkdir -p deps
cd deps
git clone https://github.com/aronfan/vimrc.git vimrc
echo "source ~/deps/vimrc/ubuntu.go.conf" > ~/.vimrc
```

Install other plugins
```
vim
:PluginInstall
```

Install the YCM on Ubuntu
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

