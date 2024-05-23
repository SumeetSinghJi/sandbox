class Vedic < Formula
  desc "vedic-lang is a Sanskrit programming language"
  homepage "https://github.com/vedic-lang/vedic"
  version "2.0.5"
  license "MIT"

  livecheck do
    url :stable
    regex(/release[._-](\d+(?:\.\d+)+)/i)
    strategy :github_latest
  end

  if OS.mac?
    if Hardware::CPU.arm?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-darwin-aarch64.tar.gz"
      sha256 "32fd11895f413052758d8f5cb36a48d5308c58124e0b76e029fd2bba9f46bdc2"
    elsif Hardware::CPU.intel?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-darwin-x86_64.tar.gz"
      sha256 "b6abd65541078fc79ca4ed80ba296bcfd30602de2f31be1c79d8584e38e374fb"
    else
      odie "This platform is not supported."
    end
  elsif OS.linux?
    if Hardware::CPU.arm? && Hardware::CPU.is_64_bit?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-linux-gnu-aarch64.tar.xz"
      sha256 "97e3e8caea31d8dd20e14e8aa121fe6fc8878c46e63e5641ec18fae63b7711a0"
    elsif Hardware::CPU.intel? && Hardware::CPU.is_64_bit?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-linux-gnu-x86_64.tar.xz"
      sha256 "3a60cb40c7e8e3b38552314ccf33ad5f035f1420a8ef9913f1db8291551a2534"
    elsif Hardware::CPU.intel? && Hardware::CPU.is_32_bit?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-linux-gnu-i686.tar.xz"
      sha256 "40f1dc5d03c7bb9976cffb1a842c3eb1cc6ff254ebed4c1fea24cdaa0a173ed3"
    elsif Hardware::CPU.arm? && Hardware::CPU.is_32_bit?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-linux-gnueabihf-armv7.tar.xz"
      sha256 "4ca0b424df857d4aca4e3519529d40d9443ada09d5c3f99379d625ca0dc7a89b"
    elsif Hardware::CPU.intel? && Hardware::CPU.is_64_bit? && OS::Linux::Musl.is_detected?
      url "https://github.com/vedic-lang/vedic/releases/download/v2.0.5/vedic-linux-musl-x86_64.tar.xz"
      sha256 "c88ce8c427a3083ab706ed31485ff6118e99291052408f9752b167514f929e2d"
    else
      odie "This platform is not supported."
    end
  else
    odie "This platform is not supported."
  end

  def install
    bin.install "vedic"
  end

  def caveats
    <<~EOS
      To get started, run:
        vedic --help
    EOS
  end

  test do
    assert_predicate bin/"vedic", :exist?, "The 'vedic' binary does not exist."
    assert_match "vedic-lang", shell_output("#{bin}/vedic --help")
  end
end
