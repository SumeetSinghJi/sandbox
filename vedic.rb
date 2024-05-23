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

  depends_on "rust" => :build

  def install
    arch = Hardware::CPU.arm? ? "aarch64-apple-darwin" : "x86_64-apple-darwin"

    # Install the appropriate rust target
    system "rustup", "target", "add", arch, "--toolchain", "stable"

    # Build for the specific architecture
    system "cargo", "build", "--release", "--target", arch
    bin.install "target/#{arch}/release/vedic"
  end

  def caveats
    <<~EOS
      To get started, run:
        vedic --help
    EOS
  end

  test do
    assert_match "Usage:", shell_output("#{bin}/vedic --help")
  end
end
