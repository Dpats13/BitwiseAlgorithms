# -*- mode: ruby -*-
# vi: set ft=ruby :

# Vagrantfile API/syntax version. Don't touch unless you know what you're doing!
VAGRANTFILE_API_VERSION = "2"

Vagrant.configure(VAGRANTFILE_API_VERSION) do |config|
  config.vm.box = "ubuntu/xenial64"
  #config.vm.box_url = "https://vagrantcloud.com/ubuntu/boxes/xenial64/versions/20180105.0.0/providers/virtualbox.box"

  config.vm.provider :virtualbox do |vb|
    vb.cpus = 1
    vb.memory = 512
  end
 
  # Automatically use local apt-cacher-ng if available
  if File.exists? "/etc/apt-cacher-ng"
    # If apt-cacher-ng is installed on this machine then just use it.
    require 'socket'
    guessed_address = Socket.ip_address_list.detect{|intf| !intf.ipv4_loopback?}
    if guessed_address
      config.vm.provision :shell, :inline => "echo 'Acquire::http { Proxy \"http://#{guessed_address.ip_address}:3142\"; };' > /etc/apt/apt.conf.d/02proxy"
    end
  end

  # Update to have the latest packages, remove if you don't need that
  config.vm.provision :shell, :inline => "apt-get update"
  config.vm.provision :shell, :inline => "apt-get install -y build-essential gcc-multilib emacs htop"
  config.vm.provision :shell, :inline => "echo 'cd /vagrant' >>/home/ubuntu/.bashrc"
  config.vm.provision :shell, :inline => "curl http://www.cse.psu.edu/~tuz68/.emacs 2>/dev/null >/home/ubuntu/.emacs; chown ubuntu:ubuntu /home/ubuntu/.emacs"
  config.vm.provision :shell, :inline => "curl https://raw.githubusercontent.com/mitthu/cmpsc473_spring18/master/base/dot_vimrc 2>/dev/null >/home/ubuntu/.vimrc; chown ubuntu:ubuntu /home/ubuntu/.vimrc"
end
