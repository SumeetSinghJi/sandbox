class Vedic < Formula
  desc "Sanskrit programming language written with Rust"
  homepage "https://github.com/vedic-lang/vedic"
  version "2.0.6"
  url "https://github.com/vedic-lang/vedic/archive/refs/tags/v#{version}.tar.gz"
  sha256 "5453386fcebfa48a5f3d39bc832d19edaaaa98d8d36841428ff6a20db0dd0151"
  
  livecheck do
    url :stable
    regex(/release[._-](\d+(?:\.\d+)+)/i)
    strategy :github_latest
  end

  def install
    on_macos do
      on_arm do
        url "https://github.com/vedic-lang/vedic/releases/download/v#{version}/vedic-darwin-aarch64.tar.gz"
        sha256 "bbd827b70e20b8ac1821b5e56d9fa5e7195327ea50a71df912c3088795b1384e"
      end
      on_intel do
        url "https://github.com/vedic-lang/vedic/releases/download/v#{version}/vedic-darwin-x86_64.tar.gz"
        sha256 "ba554488af61165703a20d32df31174daff54056979b4a80504da35a003e4c41"
      end
    end

    # Download and install macOS binaries
    ohai "Downloading macOS binaries..."
    system "curl", "-OL", "#{binary_url}"
    system "tar", "xzf", "#{binary_filename}"
    bin.install "vedic" # Install the binary

    # Cleanup
    system "rm", "#{binary_filename}"
  end

  def caveats
    <<~EOS
      To get started, run:
        vedic --help
    EOS
  end

  test do
    # Simple test to verify the binary is installed
    assert_match "Usage:", shell_output("#{bin}/vedic --help")
  end
end
